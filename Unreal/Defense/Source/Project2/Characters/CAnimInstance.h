#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Components/Objects/CItemComponent.h"
#include "CAnimInstance.generated.h"

UCLASS()
class PROJECT2_API UCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UFUNCTION()
		void UpdateItemType(AActor* InActor);

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float Speed;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float Direction;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		bool bInAir;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		 EItemType ItemType;

public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};