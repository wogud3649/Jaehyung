#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CInteractComponent.generated.h"

UENUM(BlueprintType)
enum class EInteractType : uint8
{
	Default, Hold, Toggle, Max,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInteract, AActor*, InActor);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT2_API UCInteractComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	FORCEINLINE void SetHold() { ChangeType(EInteractType::Hold); }
	FORCEINLINE void SetToggle() { ChangeType(EInteractType::Toggle); }

	FORCEINLINE EInteractType GetType() { return Type; }

public:
	UPROPERTY(BlueprintAssignable)
		FInteract OnInteract;

	UPROPERTY(BlueprintAssignable)
		FInteract OffInteract;

private:
	UPROPERTY(EditAnywhere)
		EInteractType Type;

public:
	UCInteractComponent();

protected:
	virtual void BeginPlay() override;

public:
	void BeginInteract(AActor* InActor);
	void EndInteract(AActor* InActor);

private:
	void ChangeType(EInteractType InType);
	void Interact(AActor* InActor, bool bInInteract);

private:
	AActor* Actor;
	bool bInteract;
};