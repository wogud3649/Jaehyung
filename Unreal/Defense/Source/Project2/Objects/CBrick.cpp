#include "CBrick.h"
#include "Global.h"

ACBrick::ACBrick()
{
	UMaterialInterface* material;
	CHelpers::GetAsset<UMaterialInterface>(&material, "Material'/Game/InfinityBladeGrassLands/Environments/Plains/Env_Plains_Floors/Materials/M_Plains_Floors_Block.M_Plains_Floors_Block'");
	Mesh->SetMaterial(0, material);
}

void ACBrick::BeginPlay()
{
	Super::BeginPlay();
}

void ACBrick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}