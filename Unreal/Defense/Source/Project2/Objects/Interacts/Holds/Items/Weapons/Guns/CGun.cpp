#include "CGun.h"
#include "Global.h"
#include "Components/Objects/CGunComponent.h"
#include "Components/Objects/CItemComponent.h"
#include "Components/Utilities/CTraceComponent.h"
#include "Components/Utilities/Timelines/Floats/CZoomComponent.h"

ACGun::ACGun()
{
	CHelpers::CreateActorComponent<UCGunComponent>(this, &Gun, "Gun");
	CHelpers::CreateActorComponent<UCTraceComponent>(this, &Trace, "Trace");
	CHelpers::CreateActorComponent<UCZoomComponent>(this, &Zoom, "Zoom");

	Item->SetType(EItemType::Gun);
}

void ACGun::BeginPlay()
{
	Super::BeginPlay();
}

void ACGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Zoom->TickTimeline(DeltaTime);
}