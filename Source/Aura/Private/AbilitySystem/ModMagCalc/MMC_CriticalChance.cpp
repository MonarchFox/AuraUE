// Coded By MonarchFox


#include "AbilitySystem/ModMagCalc/MMC_CriticalChance.h"
#include "AbilitySystem/AuraAttributeSet.h"

UMMC_CriticalChance::UMMC_CriticalChance()
{
	InitCaptureDefinition(MaxDef, UAuraAttributeSet::GetIntelligenceAttribute());
}

float UMMC_CriticalChance::Execute(const FGameplayEffectSpec& Spec,
	const FAggregatorEvaluateParameters& EvaluateParameters) const
{
	const float PlayerLevel = GetPlayerLevel(Spec);
	const float LevelMultiplier = PlayerLevel / (1000);
	const float StatBuff = GetAttribute(MaxDef, Spec, EvaluateParameters) * StatMultiplier;

	return (BaseCriticalChance + LevelMultiplier + StatBuff) / 100;
}
