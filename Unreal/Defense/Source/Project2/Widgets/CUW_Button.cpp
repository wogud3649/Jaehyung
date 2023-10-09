#include "CUW_Button.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "CUW_Store.h"
#include "Components/Characters/Player/CStoreComponent.h"

void UCUW_Button::OnPressed()
{
	GetStore()->Pressed(GetName());
}

UCUW_Store* UCUW_Button::GetStore()
{
	UCStoreComponent* store = CHelpers::GetComponent<UCStoreComponent>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (store)
	{
		return store->GetStore();
	}

	return NULL;
}