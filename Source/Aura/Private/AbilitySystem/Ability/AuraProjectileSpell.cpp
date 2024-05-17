// Coded By MonarchFox


#include "AbilitySystem/Ability/AuraProjectileSpell.h"
#include "Actor/Projectile/AuraProjectileBase.h"
#include "Interaction/CombatInterface.h"
#include "Kismet/KismetSystemLibrary.h"

void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	const bool bIsServer = HasAuthority(&ActivationInfo);
	if (!bIsServer) return;

	if (const ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo()))
	{
		const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();

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
		
		Projectile->FinishSpawning(SpawnTransform);
		Projectile->SetLifeSpan(5.f);
	}
}
