// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

UMyGameInstance::UMyGameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> dataTable(TEXT("DataTable'/Game/Data/StatTable.StatTable'"));

	_dataTable = dataTable.Object;
}

void UMyGameInstance::Init()
{
	Super::Init();

	FCharacterStat* stat = GetStatByLevel(1);

	UE_LOG(LogTemp, Warning, TEXT("MaxHP : %d"), stat->maxHp);
	UE_LOG(LogTemp, Warning, TEXT("Atk : %d"), stat->attack);
}

FCharacterStat* UMyGameInstance::GetStatByLevel(int32 level)
{
	FName name = *FString::FromInt(level);
	FCharacterStat* result = _dataTable->FindRow<FCharacterStat>(name, TEXT(""));

	return result;
}
