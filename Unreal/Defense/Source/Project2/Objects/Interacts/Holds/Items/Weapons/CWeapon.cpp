#include "CWeapon.h"
#include "Global.h"
#include "Components/Objects/CWeaponComponent.h"

ACWeapon::ACWeapon()
{
	CHelpers::CreateActorComponent<UCWeaponComponent>(this, &Weapon, "Weapon");
}

void ACWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void ACWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}