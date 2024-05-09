// Coded By MonarchFox
#include "AbilitySystem/ModMagCalc/MMC_ManaMax.h"
#include "AbilitySystem/AuraAttributeSet.h"


UMMC_ManaMax::UMMC_ManaMax()
{
	InitCaptureDefinition(IntelligenceDef,
		UAuraAttributeSet::GetIntelligenceAttribute());
}

float UMMC_ManaMax::Execute(const FGameplayEffectSpec& Spec,
	const FAggregatorEvaluateParameters& EvaluateParameters) const
{
	const float Intelligence = GetAttribute(IntelligenceDef, Spec, EvaluateParameters);
	const float PlayerLevel = GetPlayerLevel(Spec);
	
	return BaseMana
					+ (IntelligenceMultiplier * Intelligence)
					+ (LevelMultiplier * PlayerLevel);
}
