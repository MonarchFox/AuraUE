// Coded By MonarchFox

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/ModMagCalc/MMC_Base.h"
#include "MMC_CriticalResistance.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UMMC_CriticalResistance : public UMMC_Base
{
	GENERATED_BODY()
public:
	UMMC_CriticalResistance();
	virtual float Execute(const FGameplayEffectSpec& Spec,
	const FAggregatorEvaluateParameters& EvaluateParameters) const override;
};
