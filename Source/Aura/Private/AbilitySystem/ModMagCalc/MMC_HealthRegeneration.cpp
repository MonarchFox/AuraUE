// Coded By MonarchFox


#include "AbilitySystem/ModMagCalc/MMC_HealthRegeneration.h"

UMMC_HealthRegeneration::UMMC_HealthRegeneration()
{
	
}

float UMMC_HealthRegeneration::Execute(const FGameplayEffectSpec& Spec,
	const FAggregatorEvaluateParameters& EvaluateParameters) const
{
	return Super::Execute(Spec, EvaluateParameters);
}
