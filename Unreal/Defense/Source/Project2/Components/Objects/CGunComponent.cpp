#include "CGunComponent.h"
#include "Global.h"
#include "Objects/Interacts/Holds/Items/Weapons/Guns/CGun.h"

void UCGunComponent::Fire(FHitResult InHitResult)
{
	ACGun* gun = Cast<ACGun>(GetOwner());
	if (gun->Fire(InHitResult))
	{
		ActiveBullets--;
		if (ActiveBullets < 0)
			ActiveBullets = 0;
	}
}

UCGunComponent::UCGunComponent()
{
}

void UCGunComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCGunComponent::Reload()
{
	ACGun* gun = Cast<ACGun>(GetOwner());
	if (gun->Reload())
		ActiveBullets = BulletCapacity;
}