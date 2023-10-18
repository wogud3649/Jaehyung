#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/Items/CItemComponent.h"
#include "CInventoryComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEFENSERPG_API UCInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere)
		TSubclassOf<class UCUW_Inventory> InventoryWidgetClass;

public:
	UCInventoryComponent();

protected:
	virtual void BeginPlay() override;

public:
	bool RootItem(class ACItem* InItem);
	void DumpItem(int32 Index);

	void SelectItem(int32 Index);

	void PlayAction(bool bLeftClick);

private:
	UCUW_Inventory* InventoryWidget;
};