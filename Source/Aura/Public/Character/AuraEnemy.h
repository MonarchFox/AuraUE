// Coded By MonarchFox

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "AuraEnemy.generated.h"

/**
 *		!Implements Enemy Character
 */

UCLASS(Blueprintable)
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

public:
	AAuraEnemy();

	// Section Interface

	// Sub-Section EnemyInterface

	virtual void HighLightActor() override;
	virtual void UnHighLightActor() override;
	void SetHighLightStencil(const float Value, const bool Status) const;
	
	UPROPERTY(EditDefaultsOnly, Category="Custom")
	int32 HighlightStencilValue { 250 };

	// End Interface
};
