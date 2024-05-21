// Coded By MonarchFox

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Ability/AuraGameplayAbility.h"
#include "AuraProjectileSpell.generated.h"


class AAuraProjectileCast;
class AAuraProjectileBase;

/**
 *		Represents Casting Spells
 */
UCLASS()
class AURA_API UAuraProjectileSpell : public UAuraGameplayAbility
{
	GENERATED_BODY()

	//? Details Panel
	UPROPERTY(EditAnywhere, Category="Custom", meta=(AllowPrivateAccess="true"))
	bool bSpawnFromHand { false };

	UPROPERTY(EditAnywhere, Category="Custom", meta=(AllowPrivateAccess="true"))
	float SpellLifeSpan { 5.f };

	UPROPERTY()
	AAuraProjectileCast* SpellCastComponent = nullptr;

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;
	
	//~ Init Spell
	UFUNCTION(BlueprintCallable, Category="Projectile")
	virtual void InitSpellAbility(const FVector& StartDirection);
	
	UFUNCTION(BlueprintCallable, Category="Projectile")
	virtual void ActivateSpellAbility(const FVector& FireDirection);
	
	virtual FVector GetSpawnHandLocation() const;
	virtual FVector GetSpawnWeaponLocation() const;
	
private:
	UPROPERTY(EditAnywhere, Category=Custom, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	TSubclassOf<AAuraProjectileBase> ProjectileClass;
	
	UPROPERTY(EditAnywhere, Category=Custom, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	TSubclassOf<AAuraProjectileCast> SpellCastClass;
};
