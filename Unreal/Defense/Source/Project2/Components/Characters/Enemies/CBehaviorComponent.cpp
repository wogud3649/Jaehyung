#include "CBehaviorComponent.h"
#include "Global.h"
#include "Characters/CCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

bool UCBehaviorComponent::IsWait()
{
	return GetType() == EBehaviorType::Wait;
}

bool UCBehaviorComponent::IsApproach()
{
	return GetType() == EBehaviorType::Approach;
}

bool UCBehaviorComponent::IsAction()
{
	return GetType() == EBehaviorType::Action;
}

bool UCBehaviorComponent::IsPatrol()
{
	return GetType() == EBehaviorType::Patrol;
}

bool UCBehaviorComponent::IsHitted()
{
	return GetType() == EBehaviorType::Hitted;
}

bool UCBehaviorComponent::IsAvoid()
{
	return GetType() == EBehaviorType::Avoid;
}

UCBehaviorComponent::UCBehaviorComponent()
{
}

void UCBehaviorComponent::BeginPlay()
{
	Super::BeginPlay();
}
void UCBehaviorComponent::ChangeType(EBehaviorType InType)
{
	EBehaviorType type = GetType();
	Blackboard->SetValueAsEnum(BehaviorKey, (uint8)InType);

	if (OnBehaviorTypeChanged.IsBound())
		OnBehaviorTypeChanged.Broadcast(type, InType);
}

AActor* UCBehaviorComponent::GetTarget()
{
	return Cast<AActor>(Blackboard->GetValueAsObject(TargetKey));
}

EBehaviorType UCBehaviorComponent::GetType()
{
	return (EBehaviorType)Blackboard->GetValueAsEnum(BehaviorKey);
}