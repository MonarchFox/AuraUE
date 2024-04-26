// Coded By MonarchFox

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "AuraCharacter.generated.h"

// Forward Declarations
class UCameraComponent;
class USpringArmComponent;

/**
 * @class AAuraCharacter
 * @brief Represents a character in the Aura game.
 * @details This class is a derived class of AAuraCharacterBase and adds components specific to a character.
 */
UCLASS(Blueprintable)
class AURA_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()

public:
	AAuraCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

protected:
	virtual void InitAbilityActorInfo() override;

private:

	// Section Components

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> CameraComponent;

	// End Section

	//~ Internal Methods
};
