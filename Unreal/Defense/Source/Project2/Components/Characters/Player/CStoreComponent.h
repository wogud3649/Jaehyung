#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Widgets/CUW_Store.h"
#include "CStoreComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT2_API UCStoreComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION()
		void ItemPressed(FStoreData InData);

	FORCEINLINE UCUW_Store* GetStore() { return StoreWidget; }
	FORCEINLINE bool IsDisplay() { return StoreWidget->IsDisplay(); }

private:
	UPROPERTY(VisibleDefaultsOnly)
		TSubclassOf<UCUW_Store> StoreWidgetClass;

public:
	UCStoreComponent();

protected:
	virtual void BeginPlay() override;

public:
	void OnDisplay();
	void OffDisplay();

private:
	UCUW_Store* StoreWidget;
};