#include "CUW_Result.h"
#include "Global.h"
#include "GameFramework/GameMode.h"
#include "Components/Button.h"
#include "Components/Textblock.h"
#include "Styling/SlateColor.h"

void UCUW_Result::Retry()
{
	OffDisplay();

	UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), "RestartLevel", UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

void UCUW_Result::Exit()
{
	OffDisplay();

	AGameMode* gamemode = Cast<AGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	CheckNull(gamemode);

	gamemode->EndMatch();
}

void UCUW_Result::NativeConstruct()
{
	Super::NativeConstruct();

	ResultText = Cast<UTextBlock>(GetWidgetFromName("ResultText"));

	RetryButton = Cast<UButton>(GetWidgetFromName("Retry"));
	RetryText = Cast<UTextBlock>(GetWidgetFromName("RetryText"));

	ExitButton = Cast<UButton>(GetWidgetFromName("Exit"));
	ExitText = Cast<UTextBlock>(GetWidgetFromName("ExitText"));

	if (RetryButton)
	{
		RetryButton->OnClicked.AddDynamic(this, &UCUW_Result::Retry);
	}

	if (ExitButton)
	{
		ExitButton->OnClicked.AddDynamic(this, &UCUW_Result::Exit);
	}
}

void UCUW_Result::Win()
{
	bResult = true;

	ResultText->SetText(FText::FromString("!!WINNER!!"));
	ResultText->SetColorAndOpacity(FSlateColor(FLinearColor::White));

	OnDisplay();
}

void UCUW_Result::Lose()
{
	bResult = false;

	ResultText->SetText(FText::FromString("GAME OVER"));
	ResultText->SetColorAndOpacity(FSlateColor(FLinearColor::Red));

	OnDisplay();
}

void UCUW_Result::OnDisplay()
{
	SetVisibility(ESlateVisibility::Visible);

	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeGameAndUI());
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.0f);
}

void UCUW_Result::OffDisplay()
{
	SetVisibility(ESlateVisibility::Hidden);

	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = false;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeGameOnly());
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0f);
}