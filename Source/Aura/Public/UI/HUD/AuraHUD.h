// Coded By MonarchFox

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"


struct FWidgetControllerParam;
class UAbilitySystemComponent;
class UAttributeSet;
class UOverlayWidgetController;
class UAuraUserWidget;

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

	//? Attribute Menu Size Information
	UPROPERTY(EditDefaultsOnly, Category="Custom", meta=(AllowPrivateAccess="true"))
	float AttributeMenu_XPosition { 500.f };
	UPROPERTY(EditDefaultsOnly, Category="Custom", meta=(AllowPrivateAccess="true"))
	float AttributeMenu_YPosition { 35.f };
	
public:

	//~ AttributeMenu
	UPROPERTY(EditAnywhere, Category="Custom")
	TSubclassOf<UAuraUserWidget> AttributeMenuUIClass;

	//~ Spawnable Widgets
	UPROPERTY()
	UAuraUserWidget* AttributeMenuWidget = nullptr;
	
	//~ initial Widget
	UPROPERTY()
	TObjectPtr<UAuraUserWidget> OverlayWidget;

	void InitOverlay(APlayerController* PlayerController, APlayerState* PlayerState,
		UAttributeSet* AttributeSet, UAbilitySystemComponent* AbilitySystemComponent);

	void InitSpawnableWidgets(APlayerController* PlayerController);

	//? Getters
	UOverlayWidgetController* SetOverlayWidgetController(const FWidgetControllerParam& WidgetControllerParam);
	FORCEINLINE UOverlayWidgetController* GetOverlayWidgetController() const { return OverlayWidgetController? OverlayWidgetController: nullptr; }

	//~ Attribute Menu Keys
	FORCEINLINE float GetAttributeMenu_XPosition() const { return AttributeMenu_XPosition; }
	FORCEINLINE float GetAttributeMenu_YPosition() const { return AttributeMenu_YPosition; }
	
private:

	//~ Stores Widgets for overlay
	UPROPERTY(EditAnywhere, Category="Widgets")
	TSubclassOf<UAuraUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere, Category="Widgets")
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;

};
