#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CItemComponent.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Default, Fist, OneHand, TwoHand, Wizard, Gun, Box, Max,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FItemRoot, AActor*, InActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAction, bool, bLeft);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT2_API UCItemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
		FItemRoot OnItemRoot;

	UPROPERTY(BlueprintAssignable)
		FItemRoot OffItemRoot;

	UPROPERTY(BlueprintAssignable)
		FAction OnAction;

	UPROPERTY(BlueprintAssignable)
		FAction OffAction;

private:
	UPROPERTY(EditAnywhere)
		EItemType Type;

public:
	FORCEINLINE void SetType(EItemType InType) { ChangeType(InType); }

	FORCEINLINE EItemType GetType() { return Type; }
	FORCEINLINE bool IsRooted() { return bRooted; }

public:
	UCItemComponent();

protected:
	virtual void BeginPlay() override;

public:
	void OnRoot(AActor* InActor);
	void OffRoot(AActor* InActor);

	void BeginAction(bool bLeft);
	void EndAction(bool bLeft);

private:
	void ChangeType(EItemType InType);

private:
	bool bRooted;
};