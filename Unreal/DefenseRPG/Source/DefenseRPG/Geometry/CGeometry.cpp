#include "CGeometry.h"
#include "Global.h"

ACGeometry::ACGeometry()
{
	// CreateComponent
	CHelpers::CreateComponent<USceneComponent>(this, &Scene, "Scene");
	CHelpers::CreateComponent<UStaticMeshComponent>(this, &Mesh, "Mesh");

	// Tick
 	PrimaryActorTick.bCanEverTick = true;
}

void ACGeometry::BeginPlay()
{
	Super::BeginPlay();
}

void ACGeometry::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACGeometry::SetMesh(FString InPath)
{
	UStaticMesh* mesh;
	CHelpers::GetAsset<UStaticMesh>(&mesh, InPath);
	Mesh->SetStaticMesh(mesh);
}