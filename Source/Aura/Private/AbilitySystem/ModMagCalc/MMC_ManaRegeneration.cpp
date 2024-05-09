// Coded By MonarchFox


#include "AbilitySystem/ModMagCalc/MMC_ManaRegeneration.h"

#include "AbilitySystem/AuraAttributeSet.h"

UMMC_ManaRegeneration::UMMC_ManaRegeneration()
{
	InitCaptureDefinition(IntelligenceDef, UAuraAttributeSet::GetIntelligenceAttribute());
}

float UMMC_ManaRegeneration::Execute(const FGameplayEffectSpec& Spec,
	const FAggregatorEvaluateParameters& EvaluateParameters) const
{
	const float Intelligence = GetAttribute(IntelligenceDef, Spec, EvaluateParameters);
	const float PlayerLevel = GetPlayerLevel(Spec);

	return BaseRegen
					+ IntelligenceMultiplier * Intelligence
					+ PlayerLevel / DivideLevel;
}
