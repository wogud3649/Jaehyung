#include "CTurret.h"
#include "Global.h"
#include "CAIController_Turret.h"
#include "Components/Characters/CStatusComponent.h"
#include "Components/Characters/CMontageComponent.h"
#include "Components/Characters/CInventoryComponent.h"
#include "Components/Objects/CWeaponComponent.h"
#include "Components/Objects/CItemComponent.h"
#include "Components/Utilities/CInteractComponent.h"
#include "Objects/Interacts/Holds/Items/Weapons/OneHands/CSword.h"
#include "Objects/Interacts/Holds/Items/Weapons/TwoHands/CGreatSword.h"
#include "Objects/Interacts/Holds/Items/Weapons/Guns/Projectiles/CModernPistol.h"
#include "Widgets/CUW_Name.h"
#include "Widgets/CUW_Health.h"
#include "Perception/AIPerceptionComponent.h"

void ACTurret::OnInteract(AActor* InActor)
{
	BeginInteract(InActor);
}

void ACTurret::OffInteract(AActor* InActor)
{
	EndInteract(InActor);
}

void ACTurret::OnRoot(AActor* InActor)
{
	BeginRoot(InActor);
}

void ACTurret::OffRoot(AActor* InActor)
{
	EndRoot(InActor);
}

void ACTurret::OnAction(bool bLeft)
{
	BeginAction(bLeft);
}

void ACTurret::OffAction(bool bLeft)
{
	EndAction(bLeft);
}

ACTurret::ACTurret()
{
	CHelpers::CreateComponent<UStaticMeshComponent>(this, &Scaffolding, "Scaffolding", GetMesh());
	CHelpers::CreateComponent<UWidgetComponent>(this, &NameWidget, "NameWidget", GetMesh());
	CHelpers::CreateComponent<UWidgetComponent>(this, &HealthWidget, "HealthWidget", GetMesh());

	CHelpers::CreateActorComponent<UCTurretComponent>(this, &Turret, "Turret");
	CHelpers::CreateActorComponent<UCInteractComponent>(this, &Interact, "Interact");
	CHelpers::CreateActorComponent<UCItemComponent>(this, &Item, "Item");

	SetMesh("SkeletalMesh'/Game/Resources/Mesh/Characters/SK_Mannequin/SK_Mannequin_Turret.SK_Mannequin_Turret'");
	SetAnimInstance("AnimBlueprint'/Game/Characters/Turrets/ABP_CTurret.ABP_CTurret_C'");

	Montage->SetDataTable("DataTable'/Game/Characters/DataTables/DT_SK_Mannequin.DT_SK_Mannequin'");

	UStaticMesh* staticMesh;
	CHelpers::GetAsset<UStaticMesh>(&staticMesh, "StaticMesh'/Game/Resources/Mesh/BasicShapes/Cylinder.Cylinder'");
	Scaffolding->SetStaticMesh(staticMesh);
	Scaffolding->SetRelativeScale3D(FVector(1, 1, 0.1f));
	Scaffolding->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	TSubclassOf<UCUW_Name> nameClass;
	CHelpers::GetClass<UCUW_Name>(&nameClass, "WidgetBlueprint'/Game/Widgets/BP_CUW_Name.BP_CUW_Name_C'");
	NameWidget->SetWidgetClass(nameClass);
	NameWidget->SetRelativeLocation(FVector(0, 0, 240));
	NameWidget->SetDrawSize(FVector2D(250, 96));
	NameWidget->SetWidgetSpace(EWidgetSpace::World);

	TSubclassOf<UCUW_Health> healthClass;
	CHelpers::GetClass<UCUW_Health>(&healthClass, "WidgetBlueprint'/Game/Widgets/BP_CUW_Health.BP_CUW_Health_C'");
	HealthWidget->SetWidgetClass(healthClass);
	HealthWidget->SetRelativeLocation(FVector(0, 0, 190));
	HealthWidget->SetDrawSize(FVector2D(120, 20));
	HealthWidget->SetWidgetSpace(EWidgetSpace::World);

	TeamId = 0;

	AIControllerClass = ACAIController_Turret::StaticClass();
	AutoPossessAI = EAutoPossessAI::Spawned;

	Interact->SetHold();

	Item->SetType(EItemType::Box);

	CHelpers::GetAsset<UBehaviorTree>(&BehaviorTree, "BehaviorTree'/Game/Characters/Turrets/BT_Turret.BT_Turret'");
}

void ACTurret::BeginPlay()
{
	Super::BeginPlay();

	Interact->OnInteract.AddDynamic(this, &ACTurret::OnInteract);
	Interact->OffInteract.AddDynamic(this, &ACTurret::OffInteract);

	Item->OnItemRoot.AddDynamic(this, &ACTurret::OnRoot);
	Item->OffItemRoot.AddDynamic(this, &ACTurret::OffRoot);
	Item->OnAction.AddDynamic(this, &ACTurret::OnAction);
	Item->OffAction.AddDynamic(this, &ACTurret::OffAction);

	NameWidget->InitWidget();
	HealthWidget->InitWidget();

	Status->InitHealth();
}

void ACTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	APawn* playerPawn = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn();
	CheckNull(playerPawn);
	FRotator rotator = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), playerPawn->GetActorLocation());
	NameWidget->SetWorldRotation(rotator);
	HealthWidget->SetWorldRotation(rotator);
}

void ACTurret::BeginInteract(AActor* InActor)
{
	CheckNull(InActor);

	USkeletalMeshComponent* skeletal = CHelpers::GetComponent<USkeletalMeshComponent>(InActor);
	CheckNull(skeletal);

	FTransform transform = skeletal->GetSocketTransform("Turret_Spawn");
	float yaw = Cast<ACharacter>(InActor)->GetControlRotation().Yaw;
	FRotator rotator = FRotator(0, yaw + 180, 0);
	transform.SetRotation(FQuat(rotator));

	SetActorTransform(transform);
	AttachToActor(InActor, FAttachmentTransformRules::KeepWorldTransform);
}

void ACTurret::EndInteract(AActor* InActor)
{
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
}

void ACTurret::BeginRoot(AActor* InActor)
{
	CheckNull(GetOwner());

	AttachToActor(GetOwner(), FAttachmentTransformRules::KeepWorldTransform);
}

void ACTurret::EndRoot(AActor* InActor)
{
	CheckNull(GetOwner());
}

void ACTurret::BeginAction(bool bLeft)
{
	CheckNull(GetOwner());

	if (bLeft)
		Build();
}

void ACTurret::EndAction(bool bLeft)
{
	CheckNull(GetOwner());
}

void ACTurret::SetTurret(ETurretType InType)
{
	Turret->SetType(InType);
	EquipWeapon();
}

void ACTurret::BeginSelected()
{
	Inventory->GetSelectedItem()->SetActorHiddenInGame(false);
}

void ACTurret::EndSelected()
{
	Inventory->GetSelectedItem()->SetActorHiddenInGame(true);
}

void ACTurret::InitBeginPlay()
{
	Status->InitName("Turret");
}

void ACTurret::EquipWeapon()
{
	ACWeapon* weapon = NULL;

	switch (Turret->GetType())
	{
	case ETurretType::Sword:
		weapon = GetWorld()->SpawnActor<ACSword>();
		break;
	case ETurretType::GreatSword:
		weapon = GetWorld()->SpawnActor<ACGreatSword>();
		break;
	case ETurretType::Gun:
		weapon = GetWorld()->SpawnActor<ACModernPistol>();
		break;
	}

	CheckNull(weapon);

	Inventory->Root(weapon);

	UCWeaponComponent* weaponComp = CHelpers::GetComponent<UCWeaponComponent>(weapon);
	CheckNull(weaponComp);

	ACAIController_Turret* controller = Cast<ACAIController_Turret>(GetController());
	CheckNull(controller);

	controller->SetActionRange(weaponComp->GetRange());
	controller->SetGenericTeamId(GetGenericTeamId());
	controller->PerceptionComponent->PostInitProperties();
}

void ACTurret::Build()
{
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	UCInventoryComponent* inventory = CHelpers::GetComponent<UCInventoryComponent>(GetOwner());
	CheckNull(inventory);

	inventory->Dump();
}