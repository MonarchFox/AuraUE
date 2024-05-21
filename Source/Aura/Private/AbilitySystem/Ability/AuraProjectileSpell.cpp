// Coded By MonarchFox


#include "AbilitySystem/Ability/AuraProjectileSpell.h"
#include "Actor/Projectile/AuraProjectileBase.h"
#include "Actor/Projectile/AuraProjectileCast.h"
#include "Interaction/CombatInterface.h"


void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
}

void UAuraProjectileSpell::InitSpellAbility(const FVector& StartDirection)
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer) return;

	if (const ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo()))
	{
		//? Spawn From either hand or weapon
		const FVector SocketLocation = bSpawnFromHand? GetSpawnHandLocation(): GetSpawnWeaponLocation();
		
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		
		AAuraProjectileCast* CastEffect =  GetWorld()->SpawnActorDeferred<AAuraProjectileCast>
		(
			SpellCastClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn
		);

		CastEffect->FinishSpawning(SpawnTransform);
		SpellCastComponent = CastEffect;
	}
}

void UAuraProjectileSpell::ActivateSpellAbility(const FVector& FireDirection)
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	
	if (!bIsServer) return;
	
	if (const ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo()))
	{
		if (SpellCastComponent) SpellCastComponent->Destroy();
		
		//? Spawn From either hand or weapon
		const FVector SocketLocation = bSpawnFromHand? GetSpawnHandLocation(): GetSpawnWeaponLocation();
		const FRotator Rotation = (FireDirection - SocketLocation).Rotation();
		
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		SpawnTransform.SetRotation(Rotation.Quaternion());
		
		AAuraProjectileBase* Projectile =  GetWorld()->SpawnActorDeferred<AAuraProjectileBase>
		(
			ProjectileClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn
		);

		// TODO: Set Gameplay Effect Spec
		Projectile->FinishSpawning(SpawnTransform);
		Projectile->SetLifeSpan(SpellLifeSpan);
	}
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
