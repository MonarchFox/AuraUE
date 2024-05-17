// Coded By MonarchFox

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "AuraInputConfig.h"
#include "AuraInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:

	template<class UserClass, class PressedFuncType, class ReleasedFuncType, class HeldFuncType>
	void BindAbilityActions(const UAuraInputConfig* InputConfig, UserClass* Object,
		PressedFuncType PressedFunction, ReleasedFuncType ReleasedFunction, HeldFuncType HeldFunction);
};

template <class UserClass, class PressedFuncType, class ReleasedFuncType, class HeldFuncType>
void UAuraInputComponent::BindAbilityActions(const UAuraInputConfig* InputConfig, UserClass* Object,
	PressedFuncType PressedFunction, ReleasedFuncType ReleasedFunction, HeldFuncType HeldFunction)
{
	checkf(InputConfig, TEXT("NO Input Configuration Provided to AuraInputComponent"));

	for(const FAuraInputAction& Action: InputConfig->AbilityInputActionStorage)
	{
		if (Action.InputAction && Action.InputTag.IsValid())
		{
			if (HeldFunction) BindAction(Action.InputAction, ETriggerEvent::Triggered, Object, HeldFunction, Action.InputTag);
			if (PressedFunction) BindAction(Action.InputAction, ETriggerEvent::Started, Object, PressedFunction, Action.InputTag);
			if (ReleasedFunction) BindAction(Action.InputAction, ETriggerEvent::Completed, Object, ReleasedFunction, Action.InputTag);
		}
	}
}
