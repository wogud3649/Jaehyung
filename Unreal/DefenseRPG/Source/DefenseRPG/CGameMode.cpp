#include "CGameMode.h"
#include "Global.h"
#include "Player/CPlayerController.h"
#include "Player/CPlayer.h"

ACGameMode::ACGameMode()
{
	PlayerControllerClass = ACPlayerController::StaticClass();

	CHelpers::GetClass<APawn>(&DefaultPawnClass, "Blueprint'/Game/Player/BP_CPlayer.BP_CPlayer_C'");
}