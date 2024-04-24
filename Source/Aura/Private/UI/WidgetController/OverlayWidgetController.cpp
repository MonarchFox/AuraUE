// Coded By MonarchFox


#include "UI/WidgetController/OverlayWidgetController.h"
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
 * @see HealthChanged()
 * @see MaxHealthChanged()
 *
 * @note This method is called as part of the initialization process in the UOverlayWidgetController class.
 */
void UOverlayWidgetController::BindCallbacksToDependencies()
{
	Super::BindCallbacksToDependencies();

	const UAuraAttributeSet* AuraAttributes = CastChecked<UAuraAttributeSet>(AttributeSet);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributes->GetHitPointsAttribute())
	.AddUObject(this, &UOverlayWidgetController::HealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributes->GetMaxHitPointsAttribute())
	.AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributes->GetManaPointsAttribute())
	.AddUObject(this, &UOverlayWidgetController::ManaChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributes->GetMaxManaPointsAttribute())
	.AddUObject(this, &UOverlayWidgetController::MaxManaChanged);
}

/**
 * @brief Handles the HealthChanged event.
 *
 * This method is called when the Health attribute changes. It broadcasts the new health value using the
 * OnHealthChanged event.
 *
 * @param Data The data object containing the new health value.
 *
 * @see OnHealthChanged
 * @see FOnAttributeChangeData
 */
void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

/**
 * @brief Callback function that gets triggered when the maximum health attribute changes.
 *
 * This function is called when the maximum health attribute changes. It broadcasts the new value
 * using the OnMaxHealthChanged event.
 *
 * @param Data The attribute change data containing the new value.
 *
 * @see OnMaxHealthChanged
 */
void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

/**
 * @brief Broadcasts the updated mana value.
 *
 * This method broadcasts the updated mana value by calling the OnManaChanged event.
 *
 * @param Data The data containing the new mana value.
 *
 * @see FOnAttributeChangeData
 * @see OnManaChanged
 *
 * @note This method is called in response to a mana attribute change in the game.
 */
void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChanged.Broadcast(Data.NewValue);
}

/**
 * @brief Broadcasts the change in maximum mana.
 *
 * This method broadcasts the change in maximum mana by calling the OnMaxManaChanged event with the new mana value.
 *
 * @param Data The data containing the new mana value.
 *
 * @see FOnAttributeChangeData
 * @see UAuraWidgetController
 *
 * @note This method is called when the maximum mana attribute changes.
 */
void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}
