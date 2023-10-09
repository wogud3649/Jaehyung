#include "CResultComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"

UCResultComponent::UCResultComponent()
{
	CHelpers::GetClass<UCUW_Result>(&ResultWidgetClass, "WidgetBlueprint'/Game/Widgets/BP_CUW_Result.BP_CUW_Result_C'");
}

void UCResultComponent::BeginPlay()
{
	Super::BeginPlay();

	ResultWidget = CreateWidget<UCUW_Result, APlayerController>(Cast<ACharacter>(GetOwner())->GetController<APlayerController>(), ResultWidgetClass);
	ResultWidget->AddToViewport();

	OffDisplay();
}

void UCResultComponent::Win()
{
	ResultWidget->Win();

	OnDisplay();
}

void UCResultComponent::Lose()
{
	ResultWidget->Lose();

	OnDisplay();
}

void UCResultComponent::OnDisplay()
{
	ResultWidget->OnDisplay();
}

void UCResultComponent::OffDisplay()
{
	ResultWidget->OffDisplay();
}