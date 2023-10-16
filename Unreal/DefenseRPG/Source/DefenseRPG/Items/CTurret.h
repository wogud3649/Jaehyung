#pragma once

#include "CoreMinimal.h"
#include "Items/CItem.h"
#include "CTurret.generated.h"

UCLASS()
class DEFENSERPG_API ACTurret : public ACItem
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
		UStaticMeshComponent* Mesh;

public:
	ACTurret();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void Rooted() override;
	virtual void OnSelected() override;
	virtual void OffSelected() override;
	virtual void Dumped() override;

protected:
	virtual void SetCollisionEnabled(bool bCollisionEnable) override;

private:
	bool bFollowCursor;
};