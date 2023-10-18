#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CItem.generated.h"

UCLASS()
class DEFENSERPG_API ACItem : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, Category = "Scene")
		USceneComponent* Scene;

	UPROPERTY(VisibleAnywhere, Category = "Item")
		class UCItemComponent* Item;

public:
	FORCEINLINE UCItemComponent* GetItemComponent() { return Item; }

public:
	ACItem();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void Rooted();
	virtual void OnSelected();
	virtual void OffSelected();
	virtual void Dumped();
	virtual bool PlayAction(bool bLeftClick);

protected:
	virtual void SetCollisionEnabled(bool bCollisionEnable);
};