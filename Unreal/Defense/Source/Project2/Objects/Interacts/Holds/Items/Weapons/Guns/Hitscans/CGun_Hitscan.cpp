#include "CGun_Hitscan.h"
#include "Global.h"
#include "Characters/CCharacter.h"
#include "Components/Objects/CWeaponComponent.h"
#include "Components/Objects/CGunComponent.h"
#include "Objects/CBreakable.h"

ACGun_Hitscan::ACGun_Hitscan()
{
}

void ACGun_Hitscan::BeginPlay()
{
	Super::BeginPlay();
}

void ACGun_Hitscan::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool ACGun_Hitscan::Fire(FHitResult InHitResult)
{
	if (Gun->GetActiveBullets() <= 0)
		return false;

	if (!InHitResult.bBlockingHit)
		return true;

	ACCharacter* cCharacter = Cast<ACCharacter>(InHitResult.Actor.Get());
	if (cCharacter)
	{
		ACCharacter* owner = Cast<ACCharacter>(GetOwner());
		if (cCharacter->GetTeamID() == owner->GetTeamID())
			return false;

		cCharacter->Damaged(Weapon->GetPower(), owner);
		return true;
	}

	ACBreakable* breakable = Cast<ACBreakable>(InHitResult.Actor.Get());
	if (breakable)
	{
		ACCharacter* owner = Cast<ACCharacter>(GetOwner());
		if (breakable->GetTeamID() == owner->GetTeamID())
			return false;

		breakable->Damaged(Weapon->GetPower());
		return true;
	}

	return true;
}

bool ACGun_Hitscan::Reload()
{
	return true;
}