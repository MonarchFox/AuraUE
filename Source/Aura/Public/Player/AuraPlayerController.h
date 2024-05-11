// Coded By MonarchFox

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "AuraPlayerController.generated.h"

/**
 *		!Implements Player Controller
 *		+ Controller Inputs
 *		+ Mouse Cursor
 */

// Forward Declaration

class UInputMappingContext;
class UInputAction;
class IEnemyInterface;


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

public:
	AAuraPlayerController();
	virtual void PlayerTick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	// Section Initial Setups

	void InitController() const;
	void InitCursor();

	// End Initial Setups

private:
	// Section Inputs
	
	UPROPERTY(EditAnywhere, Category="Player Input")
	TObjectPtr<UInputMappingContext> AuraInputContext;

	UPROPERTY(EditAnywhere, Category="Player Input")
	TObjectPtr<UInputAction> MoveInputAction;

	UPROPERTY(EditAnywhere, Category="Player Input")
	TObjectPtr<UInputAction> MouseInputAction;
	
	UPROPERTY(EditAnywhere, Category="Player Input")
	TObjectPtr<UInputAction> AttributeMenuInputAction;

	// Sub-Section Input Methods

	void MoveAction(const FInputActionValue& Action);
	void MouseAction(const FInputActionValue& Action);
	void AttributeMenuAction(const FInputActionValue& Action);
	
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
