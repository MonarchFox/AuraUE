// Coded By MonarchFox

#include "AbilitySystem/ModMagCalc/MMC_ArmorPenetration.h"
#include "AbilitySystem/AuraAttributeSet.h"

UMMC_ArmorPenetration::UMMC_ArmorPenetration()
{
	InitCaptureDefinition(DexirityDef, UAuraAttributeSet::GetConstitutionAttribute());
	InitCaptureDefinition(StrengthDef, UAuraAttributeSet::GetStrengthAttribute());
}

float UMMC_ArmorPenetration::Execute(const FGameplayEffectSpec& Spec,
	const FAggregatorEvaluateParameters& EvaluateParameters) const
{
	const float PlayerLevel = GetPlayerLevel(Spec);
	const float Constitution = GetAttribute(DexirityDef, Spec, EvaluateParameters);
	const float Strength = GetAttribute(StrengthDef, Spec, EvaluateParameters);

	return BaseArmor
					+ PlayerLevel
					+ StrengthMultiplier * Strength
					+ DexirityMultiplier * Constitution;
}
