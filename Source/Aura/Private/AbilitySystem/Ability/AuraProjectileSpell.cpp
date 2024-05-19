// Coded By MonarchFox


#include "AbilitySystem/Ability/AuraProjectileSpell.h"
#include "Actor/Projectile/AuraProjectileBase.h"
#include "Interaction/CombatInterface.h"


void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	const bool bIsServer = HasAuthority(&ActivationInfo);
	if (!bIsServer) return;
	
}

void UAuraProjectileSpell::InitSpellAbility()
{
	if (const ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo()))
	{
		//? Spawn From either hand or weapon
		const FVector SocketLocation = bSpawnFromHand? GetSpawnHandLocation(): GetSpawnWeaponLocation();

		// TODO: Set Rotation for spawning the projectile
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		
		AAuraProjectileBase* Projectile =  GetWorld()->SpawnActorDeferred<AAuraProjectileBase>
		(
			ProjectileClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn
		);

		// TODO: Set Gameplay Effect Spec
		CacheProjectile = Projectile;
		Projectile->FinishSpawning(SpawnTransform);
	}
}

void UAuraProjectileSpell::ActivateSpellAbility()
{
	CacheProjectile->ProjectileLaunched();
	CacheProjectile->SetLifeSpan(SpellLifeSpan);
}

FVector UAuraProjectileSpell::GetSpawnHandLocation() const
{
	if (const ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo()))
	{
		return CombatInterface->GetHandCombatSocketLocation();
	}
	return FVector();
}

FVector UAuraProjectileSpell::GetSpawnWeaponLocation() const
{
	if (const ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo()))
	{
		return CombatInterface->GetWeaponCombatSocketLocation();
	}
	return FVector();
}
