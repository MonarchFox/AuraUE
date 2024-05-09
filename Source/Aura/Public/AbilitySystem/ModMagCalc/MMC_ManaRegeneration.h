// Coded By MonarchFox

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/ModMagCalc/MMC_Base.h"
#include "MMC_ManaRegeneration.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UMMC_ManaRegeneration : public UMMC_Base
{
	GENERATED_BODY()
	FGameplayEffectAttributeCaptureDefinition IntelligenceDef;

	//~ Calculation Parameters
	UPROPERTY(EditAnywhere, Category=Custom, meta=(AllowPrivateAccess="true"))
	float BaseRegen { 1 };

	UPROPERTY(EditAnywhere, Category=Custom, meta=(AllowPrivateAccess="true"))
	float IntelligenceMultiplier { 0.05 };

	UPROPERTY(EditAnywhere, Category=Custom, meta=(AllowPrivateAccess="true"))
	float DivideLevel { 100.f };
	
public:
	UMMC_ManaRegeneration();
	virtual float Execute(const FGameplayEffectSpec& Spec,
	const FAggregatorEvaluateParameters& EvaluateParameters) const override;
};
