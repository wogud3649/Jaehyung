#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "COptionComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT2_API UCOptionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
		float HorizontalRotationRate = 45;

	UPROPERTY(EditDefaultsOnly)
		float VerticalRotationRate = 45;

public:
	UCOptionComponent();

protected:
	virtual void BeginPlay() override;
};