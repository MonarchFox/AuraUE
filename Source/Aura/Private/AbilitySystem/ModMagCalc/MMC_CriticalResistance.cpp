// Coded By MonarchFox


#include "AbilitySystem/ModMagCalc/MMC_CriticalResistance.h"

UMMC_CriticalResistance::UMMC_CriticalResistance()
{
}

float UMMC_CriticalResistance::Execute(const FGameplayEffectSpec& Spec,
	const FAggregatorEvaluateParameters& EvaluateParameters) const
{
	return Super::Execute(Spec, EvaluateParameters);
}
