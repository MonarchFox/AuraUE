// Coded By MonarchFox

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/ModMagCalc/MMC_Base.h"
#include "MMC_ManaMax.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UMMC_ManaMax : public UMMC_Base
{
	GENERATED_BODY()
	FGameplayEffectAttributeCaptureDefinition IntelligenceDef;

	//~ Calculation Values
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess), Category=Custom)
	float BaseMana { 80.f };
	
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess), Category=Custom)
	float IntelligenceMultiplier { 2.5 };

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess), Category=Custom)
	float LevelMultiplier { 10.f };
	
public:
	UMMC_ManaMax();
	virtual float Execute(const FGameplayEffectSpec& Spec,
		const FAggregatorEvaluateParameters& EvaluateParameters) const override;
};
