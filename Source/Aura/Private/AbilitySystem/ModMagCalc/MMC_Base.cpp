// Coded By MonarchFox


#include "AbilitySystem/ModMagCalc/MMC_Base.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_Base::UMMC_Base()
{
	
}

float UMMC_Base::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;
	
	return Execute(Spec, EvaluateParameters);
}

float UMMC_Base::Execute(const FGameplayEffectSpec& Spec, const FAggregatorEvaluateParameters& EvaluateParameters) const
{
	return 0.f;
}

float UMMC_Base::GetAttribute(const FGameplayEffectAttributeCaptureDefinition& Definition,
                              const FGameplayEffectSpec& Spec, const FAggregatorEvaluateParameters& EvaluateParameters) const
{
	float Value = 0.f;
	GetCapturedAttributeMagnitude(Definition, Spec, EvaluateParameters, Value);
	return Value;
}

int32 UMMC_Base::GetPlayerLevel(const FGameplayEffectSpec& Spec)
{
	const ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	checkf(CombatInterface, TEXT("PlayerLevel: Cant Find Source Object Passed Nullptr"));
	const float PlayerLevel = CombatInterface->GetPlayerLevel();
	return PlayerLevel;
}
