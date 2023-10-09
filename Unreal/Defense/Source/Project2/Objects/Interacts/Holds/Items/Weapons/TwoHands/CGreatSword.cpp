#include "CGreatSword.h"
#include "Global.h"
#include "Characters/CCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/Objects/CWeaponComponent.h"
#include "Objects/CBreakable.h"

void ACGreatSword::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
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

ACGreatSword::ACGreatSword()
{
	CHelpers::CreateComponent<USkeletalMeshComponent>(this, &Mesh, "Mesh", Scene);
	CHelpers::CreateComponent<UCapsuleComponent>(this, &Capsule, "Capsule", Mesh);

	SetMesh(Mesh, "SkeletalMesh'/Game/Resources/Mesh/Weapons/GreatSword/SK_GreatSword.SK_GreatSword'");
	Mesh->SetCollisionProfileName("Custom");
	Mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_PhysicsBody, ECollisionResponse::ECR_Overlap);
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Mesh->SetSimulatePhysics(true);

	Capsule->SetRelativeLocation(FVector(0, 0, 67));
	Capsule->SetCapsuleHalfHeight(46);
	Capsule->SetCapsuleRadius(6);

	Weapon->SetType(EWeaponType::GreatSword);
	Weapon->SetPower(20);
	Weapon->SetRange(200);
	Weapon->DeactivateCollision();
}

void ACGreatSword::BeginPlay()
{
	Super::BeginPlay();

	Capsule->OnComponentBeginOverlap.AddDynamic(this, &ACGreatSword::BeginOverlap);
}

void ACGreatSword::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACGreatSword::BeginRoot(AActor* InActor)
{
	UMeshComponent* mesh = CHelpers::GetComponent<UMeshComponent>(InActor);
	CheckNull(mesh);

	AttachToComponent_Relative(Mesh, mesh, "Item_GreatSword", true);
}

void ACGreatSword::EndRoot(AActor* InActor)
{
	UMeshComponent* mesh = CHelpers::GetComponent<UMeshComponent>(InActor);
	CheckNull(mesh);

	DetachFromComponent(Mesh, mesh, FDetachmentTransformRules::KeepWorldTransform, true);
}

void ACGreatSword::BeginAction(bool bLeft)
{
	CheckNull(GetOwner());
}

void ACGreatSword::EndAction(bool bLeft)
{
	CheckNull(GetOwner());
}