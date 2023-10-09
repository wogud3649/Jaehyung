#pragma once

#include "CoreMinimal.h"
#include "Objects/CObject.h"
#include "Interfaces/IInteract.h"
#include "CInteract.generated.h"

UCLASS()
class PROJECT2_API ACInteract : public ACObject, public IIInteract
{
	GENERATED_BODY()

public:
	UFUNCTION()
		void OnInteract(AActor* InActor);

	UFUNCTION()
		void OffInteract(AActor* InActor);

protected:
	UPROPERTY(VisibleDefaultsOnly)
		class UCInteractComponent* Interact;

public:
	ACInteract();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void BeginInteract(AActor* InActor) override {};
	virtual void EndInteract(AActor* InActor) override {};
};