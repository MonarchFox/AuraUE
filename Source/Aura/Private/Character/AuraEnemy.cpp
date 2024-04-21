// Coded By MonarchFox


#include "Character/AuraEnemy.h"


AAuraEnemy::AAuraEnemy()
{
	// !Defaults

	// + Collision Defaults
	GetMesh()-> SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	// + HighLight Defaults
	WeaponComponent->SetCustomDepthStencilValue(HighlightStencilValue);
	GetMesh()->SetCustomDepthStencilValue(HighlightStencilValue);
}

void AAuraEnemy::HighLightActor()
{
	// !Highlight actors implementation on hover
	SetHighLightStencil(HighlightStencilValue, true);
}

void AAuraEnemy::UnHighLightActor()
{
	// !UnHighlight actors implementation on end hover
	SetHighLightStencil(0.f, false);
}

void AAuraEnemy::SetHighLightStencil(const float Value, const bool Status) const
{
	// !Sets Highlight Status
	GetMesh()->SetRenderCustomDepth(Status);
	WeaponComponent->SetRenderCustomDepth(Status);

	// ? Moved to Constructor
	// GetMesh()->SetCustomDepthStencilValue(HighlightStencilValue); 
	// WeaponComponent->SetCustomDepthStencilValue(HighlightStencilValue);
}
