// Coded By MonarchFox


#include "AbilitySystem/ModMagCalc/MMC_CriticalDamage.h"

#include "AbilitySystem/AuraAttributeSet.h"

UMMC_CriticalDamage::UMMC_CriticalDamage()
{
	InitCaptureDefinition(DexDef, UAuraAttributeSet::GetDexterityAttribute());
	InitCaptureDefinition(StrDef, UAuraAttributeSet::GetStrengthAttribute());
}

float UMMC_CriticalDamage::Execute(const FGameplayEffectSpec& Spec,
	const FAggregatorEvaluateParameters& EvaluateParameters) const
{

	const float LevelBonus = GetPlayerLevel(Spec) / DivideLevel;
	
	return DexMul * GetAttribute(DexDef, Spec, EvaluateParameters)
					+ StrMul * GetAttribute(StrDef, Spec, EvaluateParameters)
					+ LevelBonus;
}
