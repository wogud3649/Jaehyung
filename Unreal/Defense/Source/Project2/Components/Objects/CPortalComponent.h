#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CPortalComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT2_API UCPortalComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		float SpawnInterval = 10.0f;

	UPROPERTY(EditAnywhere)
		bool bDrawDebug = false;

public:
	UCPortalComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void Spawn();

private:
	float Duration;
};