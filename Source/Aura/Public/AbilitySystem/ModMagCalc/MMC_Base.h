// Coded By MonarchFox

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_Base.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UMMC_Base : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:
	UMMC_Base();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
	virtual float Execute(const FGameplayEffectSpec& Spec, const FAggregatorEvaluateParameters& EvaluateParameters) const;

protected:
	/** +Returns Attribute */
	float GetAttribute(const FGameplayEffectAttributeCaptureDefinition& Definition, const FGameplayEffectSpec& Spec,
		const FAggregatorEvaluateParameters& EvaluateParameters) const;

	//~ Sets Definition and Add Relevancy
	template<class T>
	void InitCaptureDefinition(FGameplayEffectAttributeCaptureDefinition& Definition, T Attribute);

	//~ Returns Player Level
	static int32 GetPlayerLevel(const FGameplayEffectSpec& Spec);
};

template <class T>
void UMMC_Base::InitCaptureDefinition(FGameplayEffectAttributeCaptureDefinition& Definition, T Attribute)
{
	Definition.AttributeToCapture = Attribute;
	Definition.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	Definition.bSnapshot = false;
	RelevantAttributesToCapture.Add(Definition);
}
