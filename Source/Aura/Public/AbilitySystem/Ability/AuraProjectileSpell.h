// Coded By MonarchFox

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Ability/AuraGameplayAbility.h"
#include "AuraProjectileSpell.generated.h"


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

	//~ Saved Projectile
	UPROPERTY()
	AAuraProjectileBase* CacheProjectile = nullptr;

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;
	
	//~ Init Spell
	UFUNCTION(BlueprintCallable)
	virtual void InitSpellAbility();
	
	UFUNCTION(BlueprintCallable)
	virtual void ActivateSpellAbility();
	
	
	virtual FVector GetSpawnHandLocation() const;
	virtual FVector GetSpawnWeaponLocation() const;
	
private:
	UPROPERTY(EditAnywhere, Category=Custom, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	TSubclassOf<AAuraProjectileBase> ProjectileClass;
};
