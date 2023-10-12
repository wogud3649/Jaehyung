#include "CStore.h"
#include "Global.h"
#include "Components/BoxComponent.h"
#include "Components/Buildings/CStoreComponent.h"

void ACStore::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerController* playerController = Cast<APlayerController>(OtherActor->GetInstigatorController());
	CheckNull(playerController);

	Store->BeginLink(playerController);
}

void ACStore::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Store->EndLink();
}

ACStore::ACStore()
{
	// CreateComponent
	CHelpers::CreateComponent<USceneComponent>(this, &Scene, "Scene");
	CHelpers::CreateComponent<UStaticMeshComponent>(this, &Mesh, "Mesh", Scene);
	CHelpers::CreateComponent<UBoxComponent>(this, &Box, "Box", Mesh);

	// CreateActorComponent
	CHelpers::CreateActorComponent<UCStoreComponent>(this, &Store, "Store");

	// Mesh
	UStaticMesh* mesh;
	CHelpers::GetAsset<UStaticMesh>(&mesh, "StaticMesh'/Game/Resources/Buildings/Store/Meshes/Store.Store'");
	if (mesh)
		Mesh->SetStaticMesh(mesh);
	Mesh->SetRelativeScale3D(FVector(4, 4, 0.5));

	// Box
	Box->SetRelativeLocation(FVector(0, 0, 250));
	Box->SetRelativeScale3D(FVector(1.5, 1.5, 8));

	// Tick
 	PrimaryActorTick.bCanEverTick = true;
}

void ACStore::BeginPlay()
{
	Super::BeginPlay();

	Box->OnComponentBeginOverlap.AddDynamic(this, &ACStore::OnComponentBeginOverlap);
	Box->OnComponentEndOverlap.AddDynamic(this, &ACStore::OnComponentEndOverlap);
}

void ACStore::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}