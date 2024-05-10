// Coded By MonarchFox

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/ModMagCalc/MMC_Base.h"
#include "MMC_Armor.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UMMC_Armor : public UMMC_Base
{
	GENERATED_BODY()

	//~ Definitions Used for Custom Calculation
	UPROPERTY(VisibleAnywhere, Category="Definitions")
	FGameplayEffectAttributeCaptureDefinition ConstitutionDef;
	
	UPROPERTY(EditAnywhere, Category="Definitions", meta=(AllowPrivateAccess="true"))
	float ConstitutionMultiplier { 0.15f };
	
	UPROPERTY(VisibleAnywhere, Category="Definitions")
	FGameplayEffectAttributeCaptureDefinition StrengthDef;

	UPROPERTY(EditAnywhere, Category="Definitions", meta=(AllowPrivateAccess="true"))
	float StrengthMultiplier { 0.15f };
	
	UPROPERTY(EditAnywhere, Category="Definitions", meta=(AllowPrivateAccess="true"))
	float BaseArmor { 5.f };

public:
	UMMC_Armor();
	virtual float Execute(const FGameplayEffectSpec& Spec,
		const FAggregatorEvaluateParameters& EvaluateParameters) const override;
};
