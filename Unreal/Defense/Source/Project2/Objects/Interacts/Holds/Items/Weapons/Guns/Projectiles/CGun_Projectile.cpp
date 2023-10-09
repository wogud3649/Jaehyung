#include "CGun_Projectile.h"
#include "Global.h"
#include "Camera/CameraComponent.h"
#include "Components/Objects/CGunComponent.h"
#include "Objects/Interacts/Holds/Items/Expendables/CBullet.h"

ACGun_Projectile::ACGun_Projectile()
{
	Bullets.SetNum(Gun->GetBulletCapacity());
}

void ACGun_Projectile::BeginPlay()
{
	Super::BeginPlay();

	for (int32 i = 0; i < Gun->GetBulletCapacity(); i++)
	{
		ACBullet* bullet = GetWorld()->SpawnActor<ACBullet>();
		bullet->SetOwner(this);

		USkeletalMeshComponent* skeletal = CHelpers::GetComponent<USkeletalMeshComponent>(this);
		if (skeletal)
			bullet->AttachToComponent(skeletal, FAttachmentTransformRules::KeepRelativeTransform, "Muzzle");

		Bullets[i] = bullet;
	}
}

void ACGun_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool ACGun_Projectile::Fire(FHitResult InHitResult)
{
	for (int32 i = 0; i < Gun->GetBulletCapacity(); i++)
	{
		if (!Bullets[i]->IsFired())
		{

			FRotator rotator;
			if (InHitResult.bBlockingHit)
			{
				rotator = (InHitResult.Location - GetActorLocation()).Rotation();
			}
			else
			{
				UCameraComponent* camera = CHelpers::GetComponent<UCameraComponent>(GetOwner());
				if (!camera)
					return false;

				rotator = ((camera->GetComponentLocation() + camera->GetForwardVector() * 1000) - GetActorLocation()).Rotation();
			}

			Bullets[i]->Fire(rotator);
			return true;
		}
	}

	return false;
}

bool ACGun_Projectile::Reload()
{
	for (int32 i = 0; i < Gun->GetBulletCapacity(); i++)
	{
		Bullets[i]->Init();
		Bullets[i]->Reload();
	}

	return true;
}