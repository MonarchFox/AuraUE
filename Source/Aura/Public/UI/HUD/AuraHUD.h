// Coded By MonarchFox

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "AuraHUD.generated.h"


struct FWidgetControllerParam;
class UAbilitySystemComponent;
class UAttributeSet;
class UOverlayWidgetController;
class UAuraUserWidget;
class UAttributeMenuWidgetController;

/**
 * @class AAuraHUD
 * @brief The Aura HUD class.
 *
 * This class handles the HUD for the Aura game.
 */
UCLASS()
class AURA_API AAuraHUD : public AHUD
{
	GENERATED_BODY()
	
public:

	// Section Overlay

	void InitOverlay(APlayerController* PlayerController, APlayerState* PlayerState,
		UAttributeSet* AttributeSet, UAbilitySystemComponent* AbilitySystemComponent);

	//~ Getters and Setters
	UOverlayWidgetController* SetOverlayWidgetController(const FWidgetControllerParam& WidgetControllerParam);
	FORCEINLINE UOverlayWidgetController* GetOverlayWidgetController() const { return OverlayWidgetController? OverlayWidgetController: nullptr; }

	// End Overlay

	// Section Attribute Menu
	
	void InitAttributeMenuWidgets(APlayerController* PlayerController, APlayerState* PlayerState,
						   UAttributeSet* AttributeSet, UAbilitySystemComponent* AbilitySystemComponent);
	
	//~ Getters and Setters
	UAttributeMenuWidgetController* SetAttributeMenuWidgetController(const FWidgetControllerParam& WidgetControllerParam);
	FORCEINLINE UAttributeMenuWidgetController* GetAttributeMenuWidgetController() const { return AttributeMenuWidgetController; }

	// + Attribute Menu Spawn Positions
	FORCEINLINE float GetAttributeMenu_XPosition() const { return AttributeMenu_XPosition; }
	FORCEINLINE float GetAttributeMenu_YPosition() const { return AttributeMenu_YPosition; }

	// + Attribute Menu Widget Status
	FORCEINLINE void SetAttributeMenuVisibility(const ESlateVisibility Visibility) const { AttributeMenuWidget->SetVisibility(Visibility); }
	
private:

	// Section Overlay

	//+ Overlay Widget
	UPROPERTY()
	TObjectPtr<UAuraUserWidget> OverlayWidget;
	UPROPERTY(EditAnywhere, Category="Widgets|Overlay")
	TSubclassOf<UAuraUserWidget> OverlayWidgetClass;

	//+ Overlay Widget Controller
	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
	UPROPERTY(EditAnywhere, Category="Widgets|Overlay")
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;

	// End Overlay

	// Section Attribute Menu

	//+ Meta Information

	UPROPERTY(EditDefaultsOnly, Category="Widgets|AttributeMenu", meta=(AllowPrivateAccess="true"))
	float AttributeMenu_XPosition { 500.f };
	UPROPERTY(EditDefaultsOnly, Category="Widgets|AttributeMenu", meta=(AllowPrivateAccess="true"))
	float AttributeMenu_YPosition { 35.f };
	
	//+ Attribute Menu Widget
	UPROPERTY(EditAnywhere, Category="Widgets|AttributeMenu")
	TSubclassOf<UAuraUserWidget> AttributeMenuUIClass;
	UPROPERTY()
	UAuraUserWidget* AttributeMenuWidget = nullptr;

	//+ Attribute Menu Widget Controller
	UPROPERTY()
	TObjectPtr<UAttributeMenuWidgetController> AttributeMenuWidgetController;
	UPROPERTY(EditAnywhere, Category="Widgets|AttributeMenu")
	TSubclassOf<UAttributeMenuWidgetController> AttributeMenuWidgetControllerClass;

	// End Attribute Menu
};
