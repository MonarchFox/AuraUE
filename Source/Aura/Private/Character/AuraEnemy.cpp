// Coded By MonarchFox


#include "Character/AuraEnemy.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Components/WidgetComponent.h"
#include "UI/Widget/AuraUserWidget.h"


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

	// + HealthBar Widget
	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBarWidget");
	HealthBar->SetupAttachment(GetRootComponent());
}

void AAuraEnemy::BeginPlay()
{
	Super::BeginPlay();
	InitAbilityActorInfo();
	BroadcastAttribute();
}

void AAuraEnemy::InitAbilityActorInfo()
{
	Super::InitAbilityActorInfo();

	GetAbilitySystemComponent()->InitAbilityActorInfo(this, this);
	Cast<UAuraAbilitySystemComponent>(GetAbilitySystemComponent())->AbilityActorInfoSet();

	InitializeDefaultAttributes();
}

void AAuraEnemy::BroadcastAttribute()
{
	//~ BroadCast Values
	if (UAuraUserWidget* AuraUserWidget =  Cast<UAuraUserWidget>(HealthBar->GetUserWidgetObject()))
	{
		AuraUserWidget->SetWidgetController(this);
	}

	if (const UAuraAttributeSet* AttributeSet = Cast<UAuraAttributeSet>(GetAttributeSet()))
	{
		// + Health Change
		GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate
		(AttributeSet->GetHitPointsAttribute()).AddLambda
		(
			[&](const FOnAttributeChangeData& Data)
			{
				OnHealthChanged.Broadcast(Data.NewValue);
			}
		);

		// + Max Health Change
		GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate
		(AttributeSet->GetMaxHitPointsAttribute()).AddLambda
		(
			[&](const FOnAttributeChangeData& Data)
			{
				OnMaxHealthChanged.Broadcast(Data.NewValue);
			}
		);

		//~ Initial Attributes
		OnHealthChanged.Broadcast(AttributeSet->GetHitPoints());
		OnMaxHealthChanged.Broadcast(AttributeSet->GetMaxHitPoints());
	}
}

// Section Interface

void AAuraEnemy::HighLightActor()
{
	
}

void AAuraEnemy::UnHighLightActor()
{
	
}

void AAuraEnemy::SetHighLightStencil(const float Value, const bool Status) const
{
	GetMesh()->SetRenderCustomDepth(Status);
	WeaponComponent->SetRenderCustomDepth(Status);

	// ? Moved to Constructor
	// GetMesh()->SetCustomDepthStencilValue(HighlightStencilValue); 
	// WeaponComponent->SetCustomDepthStencilValue(HighlightStencilValue);
}

// End Interface
