// Coded By MonarchFox

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "Components/AudioComponent.h"
#include "GameFramework/Actor.h"
#include "AuraProjectileBase.generated.h"


//? Default Value
#define PROJECTILE_GRAVITY_SCALE 0
#define PROJECTILE_INITIAL_SPEED 2000
#define PROJECTILE_MAX_SPEED 3000

//? Forward Declarations
class USphereComponent;
class UProjectileMovementComponent;
class UNiagaraSystem;
class ICombatInterface;
class UNiagaraComponent;


UCLASS()
class AURA_API AAuraProjectileBase : public AActor
{
	GENERATED_BODY()

	//? Meta Information
	bool bHit { false };

	const ICombatInterface* OwnerActor = nullptr;
	
	UPROPERTY()
	TObjectPtr<UAudioComponent> ProjectileSound;
	
public:
	AAuraProjectileBase();

	//~ Projectile Action

	// + Damage Action
	UPROPERTY(BlueprintReadWrite, meta=(ExposeOnSpawn="true"))
	FGameplayEffectSpecHandle DamageEffectSpecHandle;

protected:
	virtual void BeginPlay() override;
	virtual void Destroyed() override;

	//~ Projectile Structure Init

	// + Sphere Component
	void InitSphereStructureComponent();

	UFUNCTION()
	void OnBeginOverlapSphereComponent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


private:
	//~ Projectile Structure
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> SphereComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

	//~ Spell Structure

	// + Effect Body
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UNiagaraComponent> BodyEffect;
	
	UPROPERTY(EditAnywhere, Category="Custom|Sound")
	TObjectPtr<USoundBase> BodySound;

	// + Effect Impact
	UPROPERTY(EditAnywhere, Category="Custom|VFX")
	TObjectPtr<UNiagaraSystem> ImpactEffect;

	UPROPERTY(EditAnywhere, Category="Custom|Sound")
	TObjectPtr<USoundBase> ImpactSound;

	// ! Check it to ignore self damage
	bool CanCollide(AActor* Actor) const;

public:
	//? Getters and setters
	//~ Structure Getters (accepts no Setters for this category)
	FORCEINLINE UProjectileMovementComponent* GetProjectileMovementComponent() const { return ProjectileMovementComponent; }
	FORCEINLINE
	
	//~ Function Settings
	void ShutDownProjectileSounds() const
	{
		if (ProjectileSound) ProjectileSound->Stop();
	}

	//** !Configure This To ignore self damage from projectile */
	void SetOwnerActor(const ICombatInterface* Actor);
		
	//~ Helper Functions
	void PlaySoundEffect(USoundBase* SFX, bool bAttach = false);
	void SpawnNiagaraEffect(UNiagaraSystem* VFX) const;
};
