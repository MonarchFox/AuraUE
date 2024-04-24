// Coded By MonarchFox

#pragma once

#include "CoreMinimal.h"
#include "Actor/AuraEffectActor.h"
#include "AuraPotionBaseGEffect.generated.h"

class USphereComponent;

/**
 * @class AAuraPotionBaseGEffect
 * @brief This class represents a base aura potion effect that can be applied to a character.
 *
 * This class inherits from AAuraEffectActor and adds functionality related to aura potion effects.
 */
UCLASS()
class AURA_API AAuraPotionBaseGEffect : public AAuraEffectActor
{
	GENERATED_BODY()

public:
	AAuraPotionBaseGEffect();

	UFUNCTION()
	void OnSphereOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:

	virtual void BeginPlay() override;
	
	//~ Components for potions
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> PotionBody;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> PotionCollisionComponent;

	//~ GameplayEffects
	UPROPERTY(EditAnywhere, Category="Custom")
	TSubclassOf<UGameplayEffect> PotionEffect;
};
