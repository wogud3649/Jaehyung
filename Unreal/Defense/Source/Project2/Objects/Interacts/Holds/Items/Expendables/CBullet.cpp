#include "CBullet.h"
#include "Global.h"
#include "Engine/TriggerVolume.h"
#include "Characters/CCharacter.h"
#include "Components/SphereComponent.h"
#include "Components/Objects/CProjectileComponent.h"
#include "Components/Objects/CWeaponComponent.h"
#include "Objects/CBreakable.h"

void ACBullet::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CheckFalse(Projectile->IsFired());

	ATriggerVolume* triggerVolume = Cast<ATriggerVolume>(OtherActor);
	if (triggerVolume)
		return;

	UCWeaponComponent* weapon = CHelpers::GetComponent<UCWeaponComponent>(GetOwner());
	CheckNull(weapon);

	ACCharacter* character = Cast<ACCharacter>(OtherActor);
	if (character)
	{
		ACCharacter* owner = Cast<ACCharacter>(GetOwner()->GetOwner());
		CheckTrue(character->GetTeamID() == owner->GetTeamID());

		character->Damaged(weapon->GetPower(), owner);
		Hit();
		return;
	}

	ACBreakable* breakable = Cast<ACBreakable>(OtherActor);
	if (breakable)
	{
		ACCharacter* owner = Cast<ACCharacter>(GetOwner()->GetOwner());
		CheckTrue(breakable->GetTeamID() == owner->GetTeamID());

		breakable->Damaged(weapon->GetPower());
		Hit();
		return;
	}

	Hit();
}

ACBullet::ACBullet()
{
	CHelpers::CreateComponent<UStaticMeshComponent>(this, &Mesh, "Mesh", Scene);
	CHelpers::CreateComponent<USphereComponent>(this, &Sphere, "Sphere", Mesh);

	CHelpers::CreateActorComponent<UCProjectileComponent>(this, &Projectile, "Projectile");

	SetActorHiddenInGame(true);

	SetMesh(Mesh, "StaticMesh'/Game/Resources/Mesh/Expendables/Shells/SM_PlasmaShot_Shell.SM_PlasmaShot_Shell'");
	Mesh->SetWorldScale3D(FVector(0.05));
	Mesh->SetCollisionProfileName("Custom");
	Mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	Sphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ACBullet::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ACBullet::BeginOverlap);
}

void ACBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Projectile->TickProjectile(DeltaTime);
}

void ACBullet::BeginRoot(AActor* InActor)
{
}

void ACBullet::EndRoot(AActor* InActor)
{
}

void ACBullet::BeginAction(bool bLeft)
{
}

void ACBullet::EndAction(bool bLeft)
{
}

void ACBullet::Fire(FRotator Direction)
{
	Projectile->Fire(Direction);

	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	SetActorRotation(Direction);
	SetActorHiddenInGame(false);

	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void ACBullet::Init()
{
	USkeletalMeshComponent* skeletal = CHelpers::GetComponent<USkeletalMeshComponent>(GetOwner());
	if (skeletal)
		AttachToComponent(skeletal, FAttachmentTransformRules::KeepRelativeTransform, "Muzzle");

	SetActorRelativeLocation(FVector(0));
	SetActorHiddenInGame(true);

	Sphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Projectile->Init();
}

void ACBullet::Reload()
{
	Projectile->Reload();
}

void ACBullet::Hit()
{
	SetActorHiddenInGame(true);

	Sphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}