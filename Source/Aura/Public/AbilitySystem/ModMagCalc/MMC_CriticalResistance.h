// Coded By MonarchFox

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/ModMagCalc/MMC_Base.h"
#include "MMC_CriticalResistance.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UMMC_CriticalResistance : public UMMC_Base
{
	GENERATED_BODY()

	FGameplayEffectAttributeCaptureDefinition ConDef;
	FGameplayEffectAttributeCaptureDefinition StrDef;

	//~ Calculation Parameters
	UPROPERTY(EditAnywhere, Category=Custom, meta=(AllowPrivateAccess="true"))
	float ConsMultiplier { 1 };

	UPROPERTY(EditAnywhere, Category=Custom, meta=(AllowPrivateAccess="true"))
	float StrMultiplier { 0.05 };

	UPROPERTY(EditAnywhere, Category=Custom, meta=(AllowPrivateAccess="true"))
	float DivideLevel { 50.f };
	
public:
	UMMC_CriticalResistance();
	virtual float Execute(const FGameplayEffectSpec& Spec,
	const FAggregatorEvaluateParameters& EvaluateParameters) const override;
};
