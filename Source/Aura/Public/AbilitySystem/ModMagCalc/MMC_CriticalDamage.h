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
public:
	UMMC_CriticalDamage();
	virtual float Execute(const FGameplayEffectSpec& Spec,
	const FAggregatorEvaluateParameters& EvaluateParameters) const override;
};
