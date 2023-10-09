#include "CCrossHairComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/Utilities/CInteractComponent.h"

void UCCrossHairComponent::Focus(FHitResult InHitResult)
{
	AActor* actor = InHitResult.GetActor();
	CheckNull(actor);

	UCInteractComponent* interact = CHelpers::GetComponent<UCInteractComponent>(actor);
	if (interact)
	{
		CrossHair->OnFocus();
		return;
	}

	CrossHair->OffFocus();
}

void UCCrossHairComponent::OnTrace(FHitResult InHitResult)
{
	AActor* actor = InHitResult.GetActor();
	CheckNull(actor);

	UCInteractComponent* interact = CHelpers::GetComponent<UCInteractComponent>(actor);
	CheckNull(interact);

	interact->BeginInteract(GetOwner());
}

void UCCrossHairComponent::OffTrace(FHitResult InHitResult)
{
	AActor* actor = InHitResult.GetActor();
	CheckNull(actor);

	UCInteractComponent* interact = CHelpers::GetComponent<UCInteractComponent>(actor);
	CheckNull(interact);

	interact->EndInteract(GetOwner());
}

UCCrossHairComponent::UCCrossHairComponent()
{
	CHelpers::GetClass<UCUW_CrossHair>(&CrossHairClass, "WidgetBlueprint'/Game/Widgets/BP_CUW_CrossHair.BP_CUW_CrossHair_C'");
}

void UCCrossHairComponent::BeginPlay()
{
	Super::BeginPlay();

	CrossHair = CreateWidget<UCUW_CrossHair, APlayerController>(Cast<ACharacter>(GetOwner())->GetController<APlayerController>(), CrossHairClass);
	CrossHair->AddToViewport();

	CrossHair->OffFocus();
}