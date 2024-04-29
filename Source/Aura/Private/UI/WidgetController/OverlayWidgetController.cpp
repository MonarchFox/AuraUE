// Coded By MonarchFox


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"


/**
 * @brief Broadcasts the initial attribute values.
 *
 * This method broadcasts the initial attribute values by calling the appropriate broadcast events.
 * It retrieves the hit points and maximum hit points from the UAuraAttributeSet and broadcasts them
 * using the OnHealthChanged and OnMaxHealthChanged events, respectively.
 *
 * @see UAuraAttributeSet
 *
 * @note This method is called as part of the initialization process in the UOverlayWidgetController class.
 */
void UOverlayWidgetController::BroadcastInitialValues()
{
	Super::BroadcastInitialValues();

	const UAuraAttributeSet* AuraAttributes = CastChecked<UAuraAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(AuraAttributes->GetHitPoints());
	OnMaxHealthChanged.Broadcast(AuraAttributes->GetMaxHitPoints());

	OnManaChanged.Broadcast(AuraAttributes->GetManaPoints());
	OnMaxManaChanged.Broadcast(AuraAttributes->GetMaxManaPoints());
}

/**
 * Binds callbacks to attribute value changes in order to update the UI accordingly.
 *
 * This method binds the HealthChanged and MaxHealthChanged callbacks to the hit points and maximum hit points attribute value changes, respectively.
 * It retrieves the hit points and maximum hit points attribute handles from the UAuraAttributeSet and registers the callbacks using the
 * GetGameplayAttributeValueChangeDelegate() method of the AbilitySystemComponent.
 *
 * @see UAuraAttributeSet
 * @see GetGameplayAttributeValueChangeDelegate()
 *
 * @note This method is called as part of the initialization process in the UOverlayWidgetController class.
 */
void UOverlayWidgetController::BindCallbacksToDependencies()
{
	Super::BindCallbacksToDependencies();

	const UAuraAttributeSet* AuraAttributes = CastChecked<UAuraAttributeSet>(AttributeSet);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributes->GetHitPointsAttribute())
	.AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			AttributeBroadcast<const FOnAttributeChangeData>(Data, OnHealthChanged);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributes->GetMaxHitPointsAttribute())
	.AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			AttributeBroadcast<const FOnAttributeChangeData>(Data, OnMaxHealthChanged);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributes->GetManaPointsAttribute())
	.AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			AttributeBroadcast<const FOnAttributeChangeData>(Data, OnManaChanged);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributes->GetMaxManaPointsAttribute())
	.AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			AttributeBroadcast<const FOnAttributeChangeData>(Data, OnMaxManaChanged);
		}
	);
	
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
		[this](const FGameplayTagContainer& AssetTags)
		{
			BroadcastWidgetRow(AssetTags, FName("Message"));
		}
	);
}

/**
 *		Delegate Message to Overlay if Tag is under Parent Tag
 *		@note specific to `FUIWidgetRow` only
 */
void UOverlayWidgetController::BroadcastWidgetRow(const FGameplayTagContainer& AssetTags, const FName ParentName) const
{
	for (const FGameplayTag& Tag: AssetTags)
	{
		//~ Broadcasting Row if parent tag matches
		if (Tag.MatchesTag(FGameplayTag::RequestGameplayTag(ParentName)))
		{
			const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(GetMessageWidgetDataTable(), Tag);
			MessageDelegate.Broadcast(*Row);
		}
	}
}
