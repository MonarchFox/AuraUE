// Coded By MonarchFox

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "AuraEnemy.generated.h"

/*****************************************************************************
 *
 *  class AAuraEnemy
 *
 *  The AAuraEnemy class is a Blueprintable class that represents an enemy in the game.
 *  It inherits from AAuraCharacterBase and IEnemyInterface.
 *
 *****************************************************************************/


UCLASS(Blueprintable)
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

public:
	AAuraEnemy();

protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;

public:
	// Section Interface

	virtual void HighLightActor() override;
	virtual void UnHighLightActor() override;
	void SetHighLightStencil(const float Value, const bool Status) const;
	
	UPROPERTY(EditDefaultsOnly, Category="Custom")
	int32 HighlightStencilValue { 250 };

	// End Interface
};
