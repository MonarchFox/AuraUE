// Coded By MonarchFox


#include "AbilitySystem/ModMagCalc/MMC_CriticalResistance.h"

#include "AbilitySystem/AuraAttributeSet.h"

UMMC_CriticalResistance::UMMC_CriticalResistance()
{
	InitCaptureDefinition(ConDef, UAuraAttributeSet::GetConstitutionAttribute());
	InitCaptureDefinition(StrDef, UAuraAttributeSet::GetStrengthAttribute());
}

float UMMC_CriticalResistance::Execute(const FGameplayEffectSpec& Spec,
	const FAggregatorEvaluateParameters& EvaluateParameters) const
{
	const float Cons = GetAttribute(ConDef, Spec, EvaluateParameters);
	const float Str = GetAttribute(StrDef, Spec, EvaluateParameters);
	const float PlayerLevel = GetPlayerLevel(Spec);

	return ConsMultiplier * Cons
								+ Str * StrMultiplier
								+ PlayerLevel / DivideLevel;
}
