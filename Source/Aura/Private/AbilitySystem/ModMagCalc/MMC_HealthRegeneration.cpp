// Coded By MonarchFox


#include "AbilitySystem/ModMagCalc/MMC_HealthRegeneration.h"

#include "AbilitySystem/AuraAttributeSet.h"

UMMC_HealthRegeneration::UMMC_HealthRegeneration()
{
	InitCaptureDefinition(ConstitutionDef, UAuraAttributeSet::GetConstitutionAttribute());
}

float UMMC_HealthRegeneration::Execute(const FGameplayEffectSpec& Spec,
	const FAggregatorEvaluateParameters& EvaluateParameters) const
{
	return BaseRegen +
		ConstitutionMultiplier * GetAttribute(ConstitutionDef, Spec, EvaluateParameters)
	+ GetPlayerLevel(Spec) / DivideLevel;
}
