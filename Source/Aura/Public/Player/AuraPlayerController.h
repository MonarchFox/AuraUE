// Coded By MonarchFox

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "AuraPlayerController.generated.h"

/**
 *		!Implements Player Controller
 *		+ Player Inputs
 *		+ Mouse Cursor
 */

// Forward Declaration

class UInputMappingContext;
class UInputAction;


UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AAuraPlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	// Section Initial Setups

	void InitController() const;
	void InitCursor();

	// End

private:
	// Section Input Declarations
	
	UPROPERTY(EditAnywhere, Category="Player Input")
	TObjectPtr<UInputMappingContext> AuraInputContext;

	UPROPERTY(EditAnywhere, Category="Player Input")
	TObjectPtr<UInputAction> MoveInputAction;

	// End

	// Section Input Methods

	void MoveAction(const FInputActionValue& Action);
	
	// End
};
