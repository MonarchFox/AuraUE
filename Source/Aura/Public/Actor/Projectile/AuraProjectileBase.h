// Coded By MonarchFox

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AuraProjectileBase.generated.h"


//? Default Value
#define PROJECTILE_GRAVITY_SCALE 0

class UNiagaraComponent;
//? Forward Declarations
class USphereComponent;
class UProjectileMovementComponent;
class UNiagaraSystem;


UCLASS()
class AURA_API AAuraProjectileBase : public AActor
{
	GENERATED_BODY()

	//? Meta Information
	bool bHit { false };
	
public:
	AAuraProjectileBase();

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

	// + Effect Impact
	UPROPERTY(EditAnywhere, Category="Custom|VFX")
	TObjectPtr<UNiagaraSystem> ImpactEffect;

	UPROPERTY(EditAnywhere, Category="Custom|Sound")
	TObjectPtr<USoundBase> ImpactSound;

public:
	//? Getters and setters
	//~ Structure Getters (accepts no Setters for this category)
	FORCEINLINE UProjectileMovementComponent* GetProjectileMovementComponent() const { return ProjectileMovementComponent; }

	//~ Helper Functions
	void PlaySoundEffect(USoundBase* SFX) const;
	void SpawnNiagaraEffect(UNiagaraSystem* VFX) const;
};
