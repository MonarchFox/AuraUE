// Coded By MonarchFox


#include "AbilitySystem/ModMagCalc/MMC_CriticalDamage.h"

UMMC_CriticalDamage::UMMC_CriticalDamage()
{
}

float UMMC_CriticalDamage::Execute(const FGameplayEffectSpec& Spec,
	const FAggregatorEvaluateParameters& EvaluateParameters) const
{
	return Super::Execute(Spec, EvaluateParameters);
}
