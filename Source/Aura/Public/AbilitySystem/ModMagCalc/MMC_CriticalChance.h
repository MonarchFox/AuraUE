// Coded By MonarchFox

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/ModMagCalc/MMC_Base.h"
#include "MMC_CriticalChance.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UMMC_CriticalChance : public UMMC_Base
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Custom Calculatio", meta=(AllowPrivateAccess="true"))
	FGameplayEffectAttributeCaptureDefinition MaxDef;
	
	UPROPERTY(EditAnywhere, Category="Custom Calculatio", meta=(AllowPrivateAccess="true"))
	float BaseCriticalChance { 5.f };

	UPROPERTY(EditAnywhere, Category="Custom Calculatio", meta=(AllowPrivateAccess="true"))
	float StatMultiplier { 0.01 };
	
public:
	UMMC_CriticalChance();
	virtual float Execute(const FGameplayEffectSpec& Spec,
		const FAggregatorEvaluateParameters& EvaluateParameters) const override;
};
