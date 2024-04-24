// Coded By MonarchFox


#include "UI/HUD/AuraHUD.h"
#include "Blueprint/UserWidget.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"


/**
 * Initializes the overlay widget for the Aura HUD.
 *
 * @param PlayerController The player controller associated with the overlay widget.
 * @param PlayerState The player state associated with the overlay widget.
 * @param AttributeSet The attribute set associated with the overlay widget.
 * @param AbilitySystemComponent The ability system component associated with the overlay widget.
 * @return void
 */
void AAuraHUD::InitOverlay(APlayerController* PlayerController, APlayerState* PlayerState,
                           UAttributeSet* AttributeSet, UAbilitySystemComponent* AbilitySystemComponent)
{
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class Uninitialized, Please fill out BP_AuraHUD"))
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class Uninitialized, Please fill out BP_AuraHUD"))

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UAuraUserWidget>(Widget);

	const FWidgetControllerParam WidgetControllerParam(PlayerController, PlayerState, AbilitySystemComponent, AttributeSet);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParam);

	OverlayWidget->SetWidgetController(WidgetController);
	WidgetController->BroadcastInitialValues();

	Widget->AddToViewport();
}

/**
 * Get the overlay widget controller for the given widget controller.
 *
 * @param WidgetControllerParam The widget controller to associate with the overlay controller.
 * @return The overlay widget controller.
 */
UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParam& WidgetControllerParam)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParam(WidgetControllerParam);
		OverlayWidgetController->BindCallbacksToDependencies();
	}
	return OverlayWidgetController;
}
