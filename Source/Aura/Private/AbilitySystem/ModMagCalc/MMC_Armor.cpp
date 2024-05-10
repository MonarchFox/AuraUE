// Coded By MonarchFox


#include "AbilitySystem/ModMagCalc/MMC_Armor.h"
#include "AbilitySystem/AuraAttributeSet.h"

UMMC_Armor::UMMC_Armor()
{
	InitCaptureDefinition(ConstitutionDef, UAuraAttributeSet::GetConstitutionAttribute());
	InitCaptureDefinition(StrengthDef, UAuraAttributeSet::GetStrengthAttribute());
}

float UMMC_Armor::Execute(const FGameplayEffectSpec& Spec,
	const FAggregatorEvaluateParameters& EvaluateParameters) const
{
	const float PlayerLevel = GetPlayerLevel(Spec);
	const float Constitution = GetAttribute(ConstitutionDef, Spec, EvaluateParameters);
	const float Strength = GetAttribute(StrengthDef, Spec, EvaluateParameters);

	return BaseArmor
					+ PlayerLevel
					+ StrengthMultiplier * Strength
					+ ConstitutionMultiplier * Constitution;
}
