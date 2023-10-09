#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "CTraceComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTrace, FHitResult, InHitResult);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT2_API UCTraceComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
		FTrace TickTrace;

	UPROPERTY(BlueprintAssignable)
		FTrace OnTrace;

	UPROPERTY(BlueprintAssignable)
		FTrace OffTrace;

private:
	UPROPERTY(EditDefaultsOnly)
		TEnumAsByte<ETraceTypeQuery> Query = UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_Camera);

	UPROPERTY(EditDefaultsOnly)
		TArray<AActor*> ActorsToIgnore;

	UPROPERTY(EditAnywhere)
		TEnumAsByte<EDrawDebugTrace::Type> DrawDebugType = EDrawDebugTrace::None;

	UPROPERTY(EditAnywhere)
		FLinearColor TraceColor = FLinearColor::Green;

	UPROPERTY(EditAnywhere)
		FLinearColor TraceHitColor = FLinearColor::Red;

	UPROPERTY(EditAnywhere)
		float DebugDuration = 1.0f;

public:	
	UCTraceComponent();

protected:
	virtual void BeginPlay() override;

public:
	void Trace(FVector InStart, FVector InEnd);
	void BeginTrace();
	void EndTrace();

	void SetActorToIgnore(AActor* InActor);
	void RemoveActorToIgnore(AActor* InActor);
	void ClearActorsToIgnore();

private:
	FHitResult HitResult;
	FHitResult TempHitResult;
};