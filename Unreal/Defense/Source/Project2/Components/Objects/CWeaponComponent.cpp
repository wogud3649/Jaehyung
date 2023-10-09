#include "CWeaponComponent.h"
#include "Global.h"
#include "Components/ShapeComponent.h"

UCWeaponComponent::UCWeaponComponent()
{
}

void UCWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCWeaponComponent::ChangeType(EWeaponType InType)
{
	Type = InType;
}

void UCWeaponComponent::ActivateCollision()
{
	TArray<UActorComponent*> actorComponents = GetOwner()->GetComponentsByClass(UShapeComponent::StaticClass());

	for (UActorComponent* actorComponent : actorComponents)
	{
		UShapeComponent* shape = Cast<UShapeComponent>(actorComponent);
		shape->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
}

void UCWeaponComponent::DeactivateCollision()
{
	TArray<UActorComponent*> actorComponents = GetOwner()->GetComponentsByClass(UShapeComponent::StaticClass());

	for (UActorComponent* actorComponent : actorComponents)
	{
		UShapeComponent* shape = Cast<UShapeComponent>(actorComponent);
		shape->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}