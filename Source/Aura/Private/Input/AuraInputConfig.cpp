// Coded By MonarchFox

#include "Input/AuraInputConfig.h"


const UInputAction* UAuraInputConfig::FindAbilityInputAction(const FGameplayTag& InputTag,
	const bool bLogNotFound) const
{
	for(const FAuraInputAction& Element: AbilityInputActionStorage)
	{
		if (Element.InputAction && Element.InputTag == InputTag)
			return Element.InputAction;
	}
	
	if (bLogNotFound) UE_LOG(LogTemp, Error,
		TEXT("Cant find AbilityInputAction for InputTag [%s], on InputConfig [%s]"),
		*InputTag.ToString(), *GetNameSafe(this));

	return nullptr;
}
