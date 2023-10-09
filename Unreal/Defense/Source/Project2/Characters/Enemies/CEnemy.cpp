#include "CEnemy.h"
#include "Global.h"
#include "CAIController.h"
#include "Components/Characters/CStatusComponent.h"
#include "Components/Characters/CMontageComponent.h"
#include "Components/Characters/CInventoryComponent.h"
#include "Components/Objects/CWeaponComponent.h"
#include "Objects/Interacts/Holds/Items/Weapons/OneHands/CSword.h"
#include "Objects/Interacts/Holds/Items/Weapons/TwoHands/CGreatSword.h"
#include "Objects/Interacts/Holds/Items/Weapons/Guns/Projectiles/CModernPistol.h"
#include "Widgets/CUW_Name.h"
#include "Widgets/CUW_Health.h"

ACEnemy::ACEnemy()
{
	CHelpers::CreateComponent<UWidgetComponent>(this, &NameWidget, "NameWidget", GetMesh());
	CHelpers::CreateComponent<UWidgetComponent>(this, &HealthWidget, "HealthWidget", GetMesh());

	SetMesh("SkeletalMesh'/Game/Resources/Mesh/Characters/SK_Mannequin/SK_Mannequin_Enemy.SK_Mannequin_Enemy'");
	SetAnimInstance("AnimBlueprint'/Game/Characters/ABP_CEnemy.ABP_CEnemy_C'");

	Montage->SetDataTable("DataTable'/Game/Characters/DataTables/DT_SK_Mannequin.DT_SK_Mannequin'");

	TeamId = 1;

	Inventory->ClearMoney();
	Inventory->AddMoney(300);

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
}

void ACEnemy::BeginPlay()
{
	Super::BeginPlay();

	NameWidget->InitWidget();
	HealthWidget->InitWidget();

	EquipWeapon();

	Status->InitHealth();
	InitBeginPlay();
}

void ACEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APawn* playerPawn = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn();
	CheckNull(playerPawn);
	FRotator rotator = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), playerPawn->GetActorLocation());
	NameWidget->SetWorldRotation(rotator);
	HealthWidget->SetWorldRotation(rotator);
}

void ACEnemy::InitBeginPlay()
{
	Status->InitName("Enemy");
}

void ACEnemy::EquipWeapon()
{
	ACWeapon* weapon = NULL;

	switch (WeaponType)
	{
	case EWeaponType::Unarmed:
		break;
	case EWeaponType::Sword:
		weapon = GetWorld()->SpawnActor<ACSword>();
		break;
	case EWeaponType::GreatSword:
		weapon = GetWorld()->SpawnActor<ACGreatSword>();
		break;
	case EWeaponType::Pistol:
		weapon = GetWorld()->SpawnActor<ACModernPistol>();
		break;
	}

	CheckNull(weapon);

	Inventory->Root(weapon);

	UCWeaponComponent* weaponComp = CHelpers::GetComponent<UCWeaponComponent>(weapon);
	CheckNull(weaponComp);

	ACAIController* controller = Cast<ACAIController>(GetController());
	CheckNull(controller);
	controller->SetActionRange(weaponComp->GetRange());
}