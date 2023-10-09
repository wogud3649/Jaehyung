#include "CTraceComponent.h"
#include "Global.h"

UCTraceComponent::UCTraceComponent()
{
}

void UCTraceComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCTraceComponent::Trace(FVector InStart, FVector InEnd)
{
	UKismetSystemLibrary::LineTraceSingle(GetWorld(), InStart, InEnd, Query, false, ActorsToIgnore, DrawDebugType, HitResult, true, TraceColor, TraceHitColor, DebugDuration);

	if (TickTrace.IsBound())
		TickTrace.Broadcast(HitResult);
}

void UCTraceComponent::BeginTrace()
{
	if (OnTrace.IsBound())
		OnTrace.Broadcast(HitResult);

	TempHitResult = HitResult;
}

void UCTraceComponent::EndTrace()
{
	if (OffTrace.IsBound())
		OffTrace.Broadcast(TempHitResult);

	TempHitResult = FHitResult();
}

void UCTraceComponent::SetActorToIgnore(AActor* InActor)
{
	ActorsToIgnore.Add(InActor);
}

void UCTraceComponent::RemoveActorToIgnore(AActor* InActor)
{
	for (int32 i = 0; i < ActorsToIgnore.Num(); i++)
	{
		if (ActorsToIgnore[i] == InActor)
			ActorsToIgnore.RemoveAt(i);
	}
}

void UCTraceComponent::ClearActorsToIgnore()
{
	ActorsToIgnore.Empty();
}