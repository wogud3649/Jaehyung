// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_FindRandPos.h"
#include "BehaviorTree/BehaviorTree.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"

UBT_FindRandPos::UBT_FindRandPos()
{
	NodeName = TEXT("FindRandPos");
}

EBTNodeResult::Type UBT_FindRandPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	UNavigationSystemV1* naviSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	if (naviSystem == nullptr)
		return EBTNodeResult::Failed;

	FNavLocation randLocation;

	if (naviSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 500.0f, randLocation))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName(TEXT("RandPos")), randLocation.Location);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
