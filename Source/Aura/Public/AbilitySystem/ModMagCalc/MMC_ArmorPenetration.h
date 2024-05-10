// Coded By MonarchFox

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/ModMagCalc/MMC_Base.h"
#include "MMC_ArmorPenetration.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UMMC_ArmorPenetration : public UMMC_Base
{
	GENERATED_BODY()
	
	//~ Definitions Used for Custom Calculation
	UPROPERTY(VisibleAnywhere, Category="Definitions")
	FGameplayEffectAttributeCaptureDefinition DexirityDef;
	
	UPROPERTY(EditAnywhere, Category="Definitions", meta=(AllowPrivateAccess="true"))
	float DexirityMultiplier { 0.15f };
	
	UPROPERTY(VisibleAnywhere, Category="Definitions")
	FGameplayEffectAttributeCaptureDefinition StrengthDef;

	UPROPERTY(EditAnywhere, Category="Definitions", meta=(AllowPrivateAccess="true"))
	float StrengthMultiplier { 0.15f };
	
	UPROPERTY(EditAnywhere, Category="Definitions", meta=(AllowPrivateAccess="true"))
	float BaseArmor { 5.f };

public:
	UMMC_ArmorPenetration();
	virtual float Execute(const FGameplayEffectSpec& Spec,
		const FAggregatorEvaluateParameters& EvaluateParameters) const override;
};
