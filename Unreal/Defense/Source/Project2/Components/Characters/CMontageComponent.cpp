#include "CMontageComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Animation/AnimMontage.h"
#include "Components/Characters/CMovementComponent.h"
#include "Components/Characters/CStatusComponent.h"

void UCMontageComponent::PlayAnimMontage(EWeaponType InWeapon, EStatusType InStatus)
{
	CheckTrue(EStatusType::Idle == InStatus);

	FMontageData* data = Datas[(int32)InWeapon][(int32)InStatus];

	if (!data)
	{
		PlayCommonMontage(InStatus);
		return;
	}

	TArray<FMontage> montages = data->AnimMontages;
	if (montages.Num() <= Selected)
	{
		if (bDebug)
			CLog::Print("OverMontageSize");

		Failed();
		return;
	}

	if (!montages[Selected].AnimMontage)
	{
		if (bDebug)
			CLog::Print("NoMontage");

		Failed();
		return;
	}

	ACharacter* character = Cast<ACharacter>(GetOwner());
	character->PlayAnimMontage(montages[Selected].AnimMontage, montages[Selected].PlayRatio, montages[Selected].StartSection);

	UCMovementComponent* movement = CHelpers::GetComponent<UCMovementComponent>(character);
	CheckNull(movement);

	if (montages[Selected].bCanMove)
		movement->SetStop();
}

UCMontageComponent::UCMontageComponent()
{
}

void UCMontageComponent::BeginPlay()
{
	Super::BeginPlay();

	CheckNull(DataTable);

	TArray<FMontageData*> datas;
	DataTable->GetAllRows<FMontageData>("", datas);

	if (datas.Num() == 0)
	{
		if (bDebug)
			CLog::Print("EmptyMontageDatas");
	}

	for (FMontageData* data : datas)
	{
		Datas[(int32)data->WeaponType][(int32)data->StatusType] = data;
	}
}

void UCMontageComponent::SetDataTable(FString InPath)
{
	UDataTable* dataTable;
	CHelpers::GetAsset<UDataTable>(&dataTable, InPath);
	DataTable = dataTable;
}

void UCMontageComponent::EnableNext()
{
	bEnableNext = true;
}

void UCMontageComponent::DisableNext()
{
	bEnableNext = false;
}

void UCMontageComponent::PlayCommonMontage(EStatusType InStatus)
{
	FMontageData* data = Datas[(int32)EWeaponType::Unarmed][(int32)InStatus];

	if (!data)
	{
		if (bDebug)
			CLog::Print("NoCommonMontageData");

		Failed();
		return;
	}

	TArray<FMontage> montages = data->AnimMontages;
	if (montages.Num() <= Selected)
	{
		if (bDebug)
			CLog::Print("OverMontageSize");

		Failed();
		return;
	}

	if (!montages[Selected].AnimMontage)
	{
		if (bDebug)
			CLog::Print("NoMontage");

		Failed();
		return;
	}

	ACharacter* character = Cast<ACharacter>(GetOwner());
	character->PlayAnimMontage(montages[Selected].AnimMontage, montages[Selected].PlayRatio, montages[Selected].StartSection);

	UCMovementComponent* movement = CHelpers::GetComponent<UCMovementComponent>(character);
	CheckNull(movement);

	if (montages[Selected].bCanMove)
		movement->SetStop();
}

void UCMontageComponent::Failed()
{
	UCStatusComponent* status = CHelpers::GetComponent<UCStatusComponent>(GetOwner());
	if (status)
	{
		status->SetIdle();
	}
}