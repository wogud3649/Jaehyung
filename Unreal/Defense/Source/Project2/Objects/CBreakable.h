#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GenericTeamAgentInterface.h"
#include "CBreakable.generated.h"

UCLASS()
class PROJECT2_API ACBreakable : public APawn, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	FORCEINLINE uint8 GetTeamID() { return TeamId; }

protected:
	UPROPERTY(VisibleDefaultsOnly)
		USceneComponent* Scene;

	UPROPERTY(VisibleDefaultsOnly)
		UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleDefaultsOnly)
		class UWidgetComponent* HealthWidget;

	UPROPERTY(VisibleDefaultsOnly)
		class UCBreakableComponent* Breakable;

	UPROPERTY(EditDefaultsOnly)
		uint8 TeamId = 0;

public:
	ACBreakable();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual FGenericTeamId GetGenericTeamId() const override;

	void Init();
	void Healed(float InAmount);
	void Damaged(float InAmount);
};