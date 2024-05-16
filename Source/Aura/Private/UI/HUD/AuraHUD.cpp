// Coded By MonarchFox


#include "UI/HUD/AuraHUD.h"
#include "Blueprint/UserWidget.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/AttributeMenuWidgetController.h"
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

// Section Overlay Widget

void AAuraHUD::InitOverlay(APlayerController* PlayerController, APlayerState* PlayerState,
                           UAttributeSet* AttributeSet, UAbilitySystemComponent* AbilitySystemComponent)
{
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class Uninitialized, Please fill out BP_AuraHUD"))
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class Uninitialized, Please fill out BP_AuraHUD"))

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UAuraUserWidget>(Widget);

	const FWidgetControllerParam WidgetControllerParam(PlayerController, PlayerState, AbilitySystemComponent, AttributeSet);
	UOverlayWidgetController* WidgetController = SetOverlayWidgetController(WidgetControllerParam);

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
UOverlayWidgetController* AAuraHUD::SetOverlayWidgetController(const FWidgetControllerParam& WidgetControllerParam)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParam(WidgetControllerParam);
		OverlayWidgetController->BindCallbacksToDependencies();
	}
	return OverlayWidgetController;
}

// End Overlay Widget


// Section Attribute Menu Widget

/** Initializes Attribute Menu Widget and Set its visibility to hidden */
void AAuraHUD::InitAttributeMenuWidgets(APlayerController* PlayerController, APlayerState* PlayerState,
						   UAttributeSet* AttributeSet, UAbilitySystemComponent* AbilitySystemComponent)
{
	if (!AttributeMenuUIClass) return;
	if (!AttributeMenuWidget)
	{
		// Creating Widget
		UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), AttributeMenuUIClass);
		AttributeMenuWidget = Cast<UAuraUserWidget>(Widget);
		
		if (!AttributeMenuWidget) return;

		// Setting Up Attribute Menu Widget Controller
		const FWidgetControllerParam WidgetControllerParam(PlayerController, PlayerState, AbilitySystemComponent, AttributeSet);
		
		UAttributeMenuWidgetController* WidgetController = SetAttributeMenuWidgetController(WidgetControllerParam);
		WidgetController->SetWidgetControllerName("Attribute Menu Widget Controller");
		
		AttributeMenuWidget->SetWidgetController(WidgetController);		//? Connecting Widget To Widget Controller
		WidgetController->BroadcastInitialValues();

		// Setting Widget Props
		AttributeMenuWidget->AddToViewport();
		AttributeMenuWidget->SetPositionInViewport(FVector2d(GetAttributeMenu_XPosition(),
			GetAttributeMenu_YPosition()));

		AttributeMenuWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

/** Create or return if already created Attribute Menu Widget Controller Responsible for Dynamic Responses to the widgets */
UAttributeMenuWidgetController* AAuraHUD::SetAttributeMenuWidgetController(
	const FWidgetControllerParam& WidgetControllerParam)
{
	if (AttributeMenuWidgetController == nullptr)
	{
		AttributeMenuWidgetController =
			NewObject<UAttributeMenuWidgetController>(this, AttributeMenuWidgetControllerClass);
		AttributeMenuWidgetController->SetWidgetControllerParam(WidgetControllerParam);
		AttributeMenuWidgetController->BindCallbacksToDependencies();
	}
	return AttributeMenuWidgetController;
}


// End Attribute Menu Widget
