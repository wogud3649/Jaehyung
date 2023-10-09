#include "CBreakable.h"
#include "Global.h"
#include "Components/Objects/CBreakableComponent.h"
#include "Components/WidgetComponent.h"
#include "Widgets/CUW_Health.h"

ACBreakable::ACBreakable()
{
	CHelpers::CreateComponent<USceneComponent>(this, &Scene, "Scene");
	CHelpers::CreateComponent<UStaticMeshComponent>(this, &Mesh, "Mesh", Scene);
	CHelpers::CreateComponent<UWidgetComponent>(this, &HealthWidget, "HealthWidget", Scene);

	CHelpers::CreateActorComponent<UCBreakableComponent>(this, &Breakable, "Breakable");

	UStaticMesh* mesh;
	CHelpers::GetAsset<UStaticMesh>(&mesh, "StaticMesh'/Game/Resources/Mesh/Objects/Breakables/SM_Env_Breakables_Box1.SM_Env_Breakables_Box1'");
	Mesh->SetStaticMesh(mesh);
	Mesh->SetRelativeScale3D(FVector(2, 2, 4));

	TSubclassOf<UCUW_Health> healthClass;
	CHelpers::GetClass<UCUW_Health>(&healthClass, "WidgetBlueprint'/Game/Widgets/BP_CUW_Health_Object.BP_CUW_Health_Object_C'");
	HealthWidget->SetWidgetClass(healthClass);
	HealthWidget->SetRelativeLocation(FVector(0, 0, 150));
	HealthWidget->SetDrawSize(FVector2D(300, 40));
	HealthWidget->SetWidgetSpace(EWidgetSpace::World);
}

void ACBreakable::BeginPlay()
{
	Super::BeginPlay();

	Breakable->InitHealth();
}

void ACBreakable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APawn* playerPawn = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn();
	CheckNull(playerPawn);
	HealthWidget->SetWorldRotation(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), playerPawn->GetActorLocation()));
	Breakable->TickBreakable(DeltaTime);
}

FGenericTeamId ACBreakable::GetGenericTeamId() const
{
	return FGenericTeamId(TeamId);
}

void ACBreakable::Init()
{
	Breakable->InitHealth();
}

void ACBreakable::Healed(float InAmount)
{
	Breakable->AddHealth(InAmount);
}

void ACBreakable::Damaged(float InAmount)
{
	Breakable->SubHealth(InAmount);
}