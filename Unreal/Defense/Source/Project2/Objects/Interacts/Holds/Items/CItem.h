#pragma once

#include "CoreMinimal.h"
#include "Objects/Interacts/Holds/CHold.h"
#include "Interfaces/IItem.h"
#include "CItem.generated.h"

UCLASS()
class PROJECT2_API ACItem : public ACHold, public IIItem
{
	GENERATED_BODY()

public:
	UFUNCTION()
		void OnRoot(AActor* InActor);

	UFUNCTION()
		void OffRoot(AActor* InActor);

	UFUNCTION()
		void OnAction(bool bLeft);

	UFUNCTION()
		void OffAction(bool bLeft);

protected:
	UPROPERTY(VisibleDefaultsOnly)
		class UCItemComponent* Item;

public:
	ACItem();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void BeginInteract(AActor* InActor) override;
	virtual void EndInteract(AActor* InActor) override;

	virtual void BeginRoot(AActor* InActor) override {};
	virtual void EndRoot(AActor* InActor) override {};
	virtual void BeginAction(bool bLeft) override {};
	virtual void EndAction(bool bLeft) override {};
};