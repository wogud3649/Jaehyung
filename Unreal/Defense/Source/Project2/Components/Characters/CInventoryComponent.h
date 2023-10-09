#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Widgets/CUW_Inventory.h"
#include "CInventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInventoryItem, AActor*, InActor);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT2_API UCInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	FORCEINLINE AActor* GetSelectedItem() { return Inventory[Selected]; }

	FORCEINLINE void ClearMoney() { Money = 0; }
	FORCEINLINE int32 GetMoney() { return Money; }

public:
	UPROPERTY(BlueprintAssignable)
		FInventoryItem SelectedItem;

private:
	UPROPERTY(VisibleDefaultsOnly)
		TSubclassOf<UCUW_Inventory> InventoryWidgetClass;

public:
	UCInventoryComponent();

protected:
	virtual void BeginPlay() override;

public:
	void SetPlayer();

	void Root(AActor* InActor);
	void Dump();
	void DumpAll();
	void DestroyAll();

	void Select(int32 index);
	void Right();
	void Left();

	void BeginAction(bool bLeft);
	void EndAction(bool bLeft);

	void Reload();

	void AddMoney(float InAmount);
	bool SubMoney(float InAmount);

private:
	void UpdateSelected();

private:
	UCUW_Inventory* InventoryWidget;
	bool bPlayer = false;

	int32 Size = 10;
	TArray<AActor*> Inventory;

	int32 Selected = 0;
	int32 OldSelected = 0;

	int32 Money = 0;
};