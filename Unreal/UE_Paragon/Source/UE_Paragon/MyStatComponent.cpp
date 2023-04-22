// Fill out your copyright notice in the Description page of Project Settings.


#include "MyStatComponent.h"

#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UMyStatComponent::UMyStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
	// ...
}


void UMyStatComponent::InitializeComponent()
{
	Super::InitializeComponent();

	SetStatByLevel(1);

	UE_LOG(LogTemp, Log, TEXT("Initialized"));
}

// Called when the game starts
void UMyStatComponent::BeginPlay()
{
	Super::BeginPlay();

	SetCurHp(_maxHp);
	// ...
	
}


// Called every frame
void UMyStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMyStatComponent::SetStatByLevel(int32 level)
{
	auto myGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (IsValid(myGameInstance))
	{
		auto stat = myGameInstance->GetStatByLevel(level);
		_level = stat->level;
		_maxHp = stat->maxHp;
		_attack = stat->attack;
		SetCurHp(_maxHp);
	}
}

void UMyStatComponent::Damaged(int32 amount)
{
	int32 newHp = _curHp - amount;
	SetCurHp(newHp);
}

void UMyStatComponent::SetCurHp(int32 hp)
{
	_curHp = hp;

	if (_curHp < 0)
	{
		_curHp = 0;
		// 죽었다는 콜백;
	}

	_onHpChangedRatio.Broadcast(HpRatio());
}

float UMyStatComponent::HpRatio()
{
	if (_maxHp <= 0.0f)
		return 0.0f;

	return (float)_curHp / (float)_maxHp;
}
