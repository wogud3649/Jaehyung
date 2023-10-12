#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CStoreComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEFENSERPG_API UCStoreComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere)
		TSubclassOf<class UCUW_Store> StoreWidgetClass;

public:
	UCStoreComponent();

protected:
	virtual void BeginPlay() override;

public:
	void BeginLink(APlayerController* PlayerController);
	void EndLink();

private:
	UCUW_Store* StoreWidget;
};