// Coded By MonarchFox


#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	Super::BindCallbacksToDependencies();
	const UAuraAttributeSet* Attributes = CastChecked<UAuraAttributeSet>(AttributeSet);
	
	for (auto& Element: Attributes->TagsToAttribute)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Element.Value()).AddLambda(
			[this, Element](const FOnAttributeChangeData& Data)
			{
				FAuraAttributeInfo Info = AttributeInformation->FindAttributeInfoForTag(Element.Key);
				Info.AttributeValue = Data.NewValue;
				AttributeInfoDelegate.Broadcast(Info);
			});
	}
}

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	const UAuraAttributeSet* Attributes = CastChecked<UAuraAttributeSet>(AttributeSet);

	//~ Primary Attribute
	checkf(AttributeInformation, TEXT("Attach Attribute Information DataAsset to Attribute Menu Widget Controller"));

	for(auto& Element: Attributes->TagsToAttribute)
	{
		FAuraAttributeInfo Info =  AttributeInformation->FindAttributeInfoForTag(Element.Key);
		Info.AttributeValue = Element.Value().GetNumericValue(Attributes);
		AttributeInfoDelegate.Broadcast(Info);
	}
}
