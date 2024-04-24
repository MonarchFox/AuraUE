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
	
public:

	//~ initial Widget
	UPROPERTY()
	TObjectPtr<UAuraUserWidget> OverlayWidget;

	void InitOverlay(APlayerController* PlayerController, APlayerState* PlayerState,
		UAttributeSet* AttributeSet, UAbilitySystemComponent* AbilitySystemComponent);

	//? Getters
	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParam& WidgetControllerParam);

private:

	//~ Stores Widgets for overlay
	UPROPERTY(EditAnywhere, Category="Widgets")
	TSubclassOf<UAuraUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere, Category="Widgets")
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
};
