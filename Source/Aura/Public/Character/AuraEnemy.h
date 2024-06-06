// Coded By MonarchFox

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "AuraEnemy.generated.h"

/*****************************************************************************
 *
 *  class AAuraEnemy
 *
 *  The AAuraEnemy class is a Blueprintable class that represents an enemy in the game.
 *  It inherits from AAuraCharacterBase and IEnemyInterface.
 *
 *****************************************************************************/


//? Forward Declarations
class UWidgetComponent;


UCLASS(Blueprintable)
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Custom", meta=(AllowPrivateAccess="true"))
	int32 PlayerLevel {1};
	
public:
	AAuraEnemy();

protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
	virtual void BroadcastAttribute();

	//~ Widget Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;

public:
	// Section Interface

	//~ Enemy Interface
	virtual void HighLightActor() override;
	virtual void UnHighLightActor() override;
	void SetHighLightStencil(const float Value, const bool Status) const;
	
	UPROPERTY(EditDefaultsOnly, Category="Custom")
	int32 HighlightStencilValue { 250 };

	//~ Combat Interface
	virtual int32 GetPlayerLevel() const override { return PlayerLevel; }
	// End Interface

	//~ Delegates
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;
};
