// Coded By MonarchFox


#include "Character/AuraEnemy.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"


AAuraEnemy::AAuraEnemy()
{
	/** !Constructor Defaults */

	// + Collision Defaults
	GetMesh()-> SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	// + HighLight Defaults
	WeaponComponent->SetCustomDepthStencilValue(HighlightStencilValue);
	GetMesh()->SetCustomDepthStencilValue(HighlightStencilValue);

	// + Ability System Defaults
	PAbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	PAbilitySystemComponent->SetIsReplicated(IsReplicationRequired());
	PAbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	PAttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
}

void AAuraEnemy::BeginPlay()
{
	Super::BeginPlay();
	GetAbilitySystemComponent()->InitAbilityActorInfo(this, this);
}

// Section Interface

/**
 * @brief Highlights the actor.
 *
 * This method is used to highlight an actor by setting the highlight stencil value.
 * The highlight effect is applied when an actor is hovered.
 */
void AAuraEnemy::HighLightActor()
{
	SetHighLightStencil(HighlightStencilValue, true);
}

/**
 * @brief UnHighLightActor is a method in the AAuraEnemy class.
 *
 * This method is used to remove the highlight effect from an actor by setting the highlight stencil value to 0.
 * The highlight effect is typically applied when an actor is no longer being hovered.
 */
void AAuraEnemy::UnHighLightActor()
{
	SetHighLightStencil(0.f, false);
}

/**
 * @brief Sets the highlight stencil value and status for the actor.
 *
 * This method is used to set the highlight status for the actor by setting the highlight stencil value.
 * It updates the custom depth rendering settings of the actor's mesh and weapon component.
 *
 * @param Value The stencil value to be set for highlighting the actor.
 * @param Status The highlight status indicating whether the actor should be highlighted or not.
 */
void AAuraEnemy::SetHighLightStencil(const float Value, const bool Status) const
{
	GetMesh()->SetRenderCustomDepth(Status);
	WeaponComponent->SetRenderCustomDepth(Status);

	// ? Moved to Constructor
	// GetMesh()->SetCustomDepthStencilValue(HighlightStencilValue); 
	// WeaponComponent->SetCustomDepthStencilValue(HighlightStencilValue);
}

// End Interface
