#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CInventoryComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEFENSERPG_API UCInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

//private:
	//UPROPERTY(VisibleAnywhere)
		//TSubclassOf<UWidgetComponent> InventoryWidget;

public:
	UCInventoryComponent();

protected:
	virtual void BeginPlay() override;
};