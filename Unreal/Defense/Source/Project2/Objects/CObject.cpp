#include "CObject.h"
#include "Global.h"
#include "Characters/CCharacter.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"

ACObject::ACObject()
{
 	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent<USceneComponent>(this, &Scene, "Scene");
}

void ACObject::BeginPlay()
{
	Super::BeginPlay();
}

void ACObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACObject::SetMesh(UStaticMeshComponent* InMesh, FString InPath)
{
	UStaticMesh* mesh;
	CHelpers::GetAsset<UStaticMesh>(&mesh, InPath);
	InMesh->SetStaticMesh(mesh);
}

void ACObject::SetMesh(USkeletalMeshComponent* InMesh, FString InPath)
{
	USkeletalMesh* mesh;
	CHelpers::GetAsset<USkeletalMesh>(&mesh, InPath);
	InMesh->SetSkeletalMesh(mesh);
}

void ACObject::SetIgnoreActor(UMeshComponent* InMesh, AActor* InActor, bool bIgnore)
{
	InMesh->IgnoreActorWhenMoving(InActor, bIgnore);
}

void ACObject::AttachToComponent_World(UMeshComponent* InMesh, USceneComponent* InParent, FName SocketName, bool bSimulatePhysics)
{
	if (bSimulatePhysics)
		InMesh->SetSimulatePhysics(false);

	InMesh->SetRelativeLocation(FVector(0));
	InMesh->SetRelativeRotation(FRotator(0));

	AttachToComponent(InParent, FAttachmentTransformRules::KeepWorldTransform, SocketName);
}

void ACObject::AttachToComponent_Relative(UMeshComponent* InMesh, USceneComponent* InParent, FName SocketName, bool bSimulatePhysics)
{
	if (bSimulatePhysics)
		InMesh->SetSimulatePhysics(false);

	SetActorRelativeLocation(FVector(0));
	SetActorRelativeRotation(FRotator(0));
	InMesh->SetRelativeLocation(FVector(0));
	InMesh->SetRelativeRotation(FRotator(0));

	AttachToComponent(InParent, FAttachmentTransformRules::KeepRelativeTransform, SocketName);
	InMesh->AttachToComponent(InParent, FAttachmentTransformRules::KeepRelativeTransform, SocketName);
	
	ACCharacter* character = Cast<ACCharacter>(InMesh->GetOwner());
	CheckNull(character);

	character->SetIgnoreActor(this);
	SetIgnoreActor(InMesh, InParent->GetOwner());
}

void ACObject::DetachFromComponent(UMeshComponent* InMesh, USceneComponent* InParent, FDetachmentTransformRules DetachmentRule, bool bSimulatePhysics)
{
	if (bSimulatePhysics)
		InMesh->SetSimulatePhysics(true);

	DetachFromActor(DetachmentRule);
	InMesh->DetachFromComponent(DetachmentRule);

	ACCharacter* character = Cast<ACCharacter>(InMesh->GetOwner());
	CheckNull(character);

	character->SetIgnoreActor(this, false);
	SetIgnoreActor(InMesh, InParent->GetOwner(), false);
}

void ACObject::SetDynamicMaterial(UMeshComponent* InMesh)
{
	TArray<UMaterialInterface*> materials = InMesh->GetMaterials();

	for (int32 index = 0; index < materials.Num(); index++)
	{
		UMaterialInstanceConstant* constantMaterial = Cast<UMaterialInstanceConstant>(materials[index]);
		if (!constantMaterial) CLog::Log(index + "Is Not Instance"); continue;

		DynamicMaterials[index] = UMaterialInstanceDynamic::Create(constantMaterial, this);
		InMesh->SetMaterial(index, DynamicMaterials[index]);
	}
}