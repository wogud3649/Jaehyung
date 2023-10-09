#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CBreakableComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT2_API UCBreakableComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	FORCEINLINE bool IsDestroyed() { return bDestroyed; }

private:
	UPROPERTY(EditDefaultsOnly)
		TArray<UStaticMesh*> MeshAssets;

	UPROPERTY(EditDefaultsOnly)
		float MaxHealth = 300;

public:
	UCBreakableComponent();

protected:
	virtual void BeginPlay() override;

public:
	void TickBreakable(float DeltaTime);

	void InitHealth();
	void AddHealth(float InAmount);
	void SubHealth(float InAmount);
	void UpdateHealth();

private:
	void UpdateMesh();

private:
	class UCUW_Health* HealthBar;
	float Health;
	
	int32 Selected = 0;

	bool bChanged;
	bool bDestroyed;

	float DestroyDelay = 5.0f;
};