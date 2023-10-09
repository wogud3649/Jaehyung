#include "CSword.h"
#include "Global.h"
#include "Characters/CCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/Objects/CWeaponComponent.h"
#include "Objects/CBreakable.h"

void ACSword::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CheckNull(GetOwner());
	CheckTrue(GetOwner() == OtherActor);

	ACCharacter* character = Cast<ACCharacter>(OtherActor);
	if (character)
	{
		ACCharacter* owner = Cast<ACCharacter>(GetOwner());
		CheckTrue(character->GetTeamID() == owner->GetTeamID());

		character->Damaged(Weapon->GetPower(), owner);
	}

	ACBreakable* breakable = Cast<ACBreakable>(OtherActor);
	if (breakable)
	{
		ACCharacter* owner = Cast<ACCharacter>(GetOwner());
		CheckTrue(breakable->GetTeamID() == owner->GetTeamID());

		breakable->Damaged(Weapon->GetPower());
	}
}

ACSword::ACSword()
{
	CHelpers::CreateComponent<USkeletalMeshComponent>(this, &Mesh, "Mesh", Scene);
	CHelpers::CreateComponent<UCapsuleComponent>(this, &Capsule, "Capsule", Mesh);

	SetMesh(Mesh, "SkeletalMesh'/Game/Resources/Mesh/Weapons/Sword/SK_Straight_Sword.SK_Straight_Sword'");
	Mesh->SetCollisionProfileName("Custom");
	Mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_PhysicsBody, ECollisionResponse::ECR_Overlap);
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Mesh->SetSimulatePhysics(true);
	Mesh->SetWorldScale3D(FVector(0.3, 0.15, 0.2));

	Capsule->SetRelativeLocation(FVector(-13, -130, 0));
	Capsule->SetRelativeRotation(FRotator(0,0,90));
	Capsule->SetCapsuleHalfHeight(160);
	Capsule->SetCapsuleRadius(16);

	Weapon->SetType(EWeaponType::Sword);
	Weapon->SetPower(10);
	Weapon->SetRange(200);
	Weapon->DeactivateCollision();
}

void ACSword::BeginPlay()
{
	Super::BeginPlay();

	Capsule->OnComponentBeginOverlap.AddDynamic(this, &ACSword::BeginOverlap);
}

void ACSword::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACSword::BeginRoot(AActor* InActor)
{
	UMeshComponent* mesh = CHelpers::GetComponent<UMeshComponent>(InActor);
	CheckNull(mesh);

	Mesh->SetWorldScale3D(FVector(1));
	AttachToComponent_Relative(Mesh, mesh, "Item_Sword", true);
}

void ACSword::EndRoot(AActor* InActor)
{
	UMeshComponent* mesh = CHelpers::GetComponent<UMeshComponent>(InActor);
	CheckNull(mesh);

	DetachFromComponent(Mesh, mesh, FDetachmentTransformRules::KeepWorldTransform, true);
	Mesh->SetWorldScale3D(FVector(0.3, 0.15, 0.2));
}

void ACSword::BeginAction(bool bLeft)
{
	CheckNull(GetOwner());
}

void ACSword::EndAction(bool bLeft)
{
	CheckNull(GetOwner());
}