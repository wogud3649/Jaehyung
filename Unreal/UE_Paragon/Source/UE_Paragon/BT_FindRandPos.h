// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BT_FindRandPos.generated.h"

/**
 * 
 */
UCLASS()
class UE_PARAGON_API UBT_FindRandPos : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBT_FindRandPos();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
};
