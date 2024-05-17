// Coded By MonarchFox

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "GameplayTagContainer.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AuraPlayerController.generated.h"

/**
 *		!Implements Player Controller
 *		+ Controller Inputs
 *		+ Mouse Cursor
 */

// Forward Declaration

struct FGameplayTag;
class UAuraInputConfig;
class UInputMappingContext;
class UInputAction;
class IEnemyInterface;
class UAuraAbilitySystemComponent;


struct FMouseInputModeGameAndUI: public FInputModeGameAndUI
{
	virtual bool ShouldFlushInputOnViewportFocus() const override { return true; }
};


/**
 *		Implements the player controller for the Aura game.
 *
 *		This class inherits from APlayerController and adds functionality for controlling the player character,
 *		handling player inputs, and managing the mouse cursor.
 *
 *		@see APlayerController
 */
UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()

	//~ Meta
	UPROPERTY()
	TObjectPtr<UAuraAbilitySystemComponent> AuraAbilitySystemComponent;

public:
	AAuraPlayerController();
	virtual void PlayerTick(float DeltaTime) override;

	//? Meta Getters
	UAuraAbilitySystemComponent* GetAuraAbilitySystemComponent()
	{
		if (!AuraAbilitySystemComponent)
		{
			AuraAbilitySystemComponent = Cast<UAuraAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
		}
		return AuraAbilitySystemComponent;
	}

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	// Section Initial Setups

	void InitController() const;
	void InitCursor();

	// End Initial Setups

private:
	// Section Inputs

	UPROPERTY(EditDefaultsOnly, Category="Player Input")
	TObjectPtr<UAuraInputConfig> AbilityInputConfig;
	
	UPROPERTY(EditDefaultsOnly, Category="Player Input")
	TObjectPtr<UInputMappingContext> AuraInputContext;

	UPROPERTY(EditDefaultsOnly, Category="Player Input")
	TObjectPtr<UInputAction> MoveInputAction;

	UPROPERTY(EditDefaultsOnly, Category="Player Input")
	TObjectPtr<UInputAction> MouseInputAction;
	
	UPROPERTY(EditDefaultsOnly, Category="Player Input")
	TObjectPtr<UInputAction> AttributeMenuInputAction;

	// Sub-Section Input Methods

	// + Movement Input Functions
	void MoveAction(const FInputActionValue& Action);
	void MouseAction(const FInputActionValue& Action);

	// + Widget Input Functions
	void AttributeMenuAction(const FInputActionValue& Action);

	// + Ability Input Functions
	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	
	// End Section Inputs

	// Section Interface

	// Sub-Section Enemy Interface
	
	IEnemyInterface* LastActor = nullptr;
	IEnemyInterface* CurrentActor = nullptr;

	void CursorTrace();
	void StepActor(const FHitResult& CHit);
	void PerformHighlights(const FHitResult& CHit) const;
	
	// End Enemy Interface
};
