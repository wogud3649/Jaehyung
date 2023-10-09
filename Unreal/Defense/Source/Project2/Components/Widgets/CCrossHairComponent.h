#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Widgets/CUW_CrossHair.h"
#include "CCrossHairComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT2_API UCCrossHairComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION()
		void Focus(FHitResult InHitResult);

	UFUNCTION()
		void OnTrace(FHitResult InHitResult);

	UFUNCTION()
		void OffTrace(FHitResult InHitResult);

private:
	UPROPERTY(VisibleDefaultsOnly)
		TSubclassOf<UCUW_CrossHair> CrossHairClass;

public:
	FORCEINLINE void OnDisplay() { CrossHair->OnDisplay(); }
	FORCEINLINE void OffDisplay() { CrossHair->OffDisplay(); }

	FORCEINLINE bool IsDisplay() { return CrossHair->IsDisplay(); }

public:
	UCCrossHairComponent();

protected:
	virtual void BeginPlay() override;

private:
	UCUW_CrossHair* CrossHair;
};