#include "CProjectileComponent.h"
#include "Global.h"
#include "Objects/Interacts/Holds/Items/Expendables/CBullet.h"

UCProjectileComponent::UCProjectileComponent()
{
}

void UCProjectileComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCProjectileComponent::TickProjectile(float DeltaTime)
{
	CheckFalse(bFired);

	if (Lifespan > 0)
	{
		GetOwner()->SetActorLocation(GetOwner()->GetActorLocation() + Direction.Vector() * Speed * DeltaTime);

		Lifespan -= DeltaTime;
	}
	else
	{
		ACBullet* bullet = Cast<ACBullet>(GetOwner());
		CheckNull(bullet);

		bullet->Hit();
	}
}

void UCProjectileComponent::Fire(FRotator InDirection)
{
	CheckTrue(bFired);
	bFired = true;

	Direction = InDirection;
}

void UCProjectileComponent::Init()
{
}

void UCProjectileComponent::Reload()
{
	bFired = false;
	Lifespan = MaxLifespan;
}