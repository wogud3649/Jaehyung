#include "CStoreComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Widgets/CUW_Store.h"

UCStoreComponent::UCStoreComponent()
{
	CHelpers::GetClass<UCUW_Store>(&StoreWidgetClass, "WidgetBlueprint'/Game/Widgets/BP_CUW_Store.BP_CUW_Store_C'");
}

void UCStoreComponent::BeginPlay()
{
	Super::BeginPlay();

	StoreWidget = CreateWidget<UCUW_Store, APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0), StoreWidgetClass);
	StoreWidget->AddToViewport();
	StoreWidget->SetVisibility(ESlateVisibility::Hidden);
}

void UCStoreComponent::BeginLink(APlayerController* PlayerController)
{
	StoreWidget->SetVisibility(ESlateVisibility::Visible);
	StoreWidget->SetLinkedPlayer(PlayerController);
}

void UCStoreComponent::EndLink()
{
	StoreWidget->SetVisibility(ESlateVisibility::Hidden);
	StoreWidget->SetLinkedPlayer(nullptr);
}