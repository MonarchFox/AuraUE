// Coded By MonarchFox

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/ModMagCalc/MMC_Base.h"
#include "MMC_CriticalDamage.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UMMC_CriticalDamage : public UMMC_Base
{
	GENERATED_BODY()

	FGameplayEffectAttributeCaptureDefinition DexDef;
	FGameplayEffectAttributeCaptureDefinition StrDef;

	//~ Calculation Parameters
	UPROPERTY(EditAnywhere, Category=Custom, meta=(AllowPrivateAccess="true"))
	float DexMul { .30f };

	UPROPERTY(EditAnywhere, Category=Custom, meta=(AllowPrivateAccess="true"))
	float StrMul { 0.20f };

	UPROPERTY(EditAnywhere, Category=Custom, meta=(AllowPrivateAccess="true"))
	float DivideLevel { 100.f };
	
public:
	UMMC_CriticalDamage();
	virtual float Execute(const FGameplayEffectSpec& Spec,
	const FAggregatorEvaluateParameters& EvaluateParameters) const override;
};
