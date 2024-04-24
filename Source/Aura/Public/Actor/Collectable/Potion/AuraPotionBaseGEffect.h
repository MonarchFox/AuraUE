// Coded By MonarchFox

#pragma once

#include "CoreMinimal.h"
#include "Actor/AuraEffectActor.h"
#include "AuraPotionBaseGEffect.generated.h"

class USphereComponent;

/**
 * 
 */
UCLASS()
class AURA_API AAuraPotionBaseGEffect : public AAuraEffectActor
{
	GENERATED_BODY()

public:
	AAuraPotionBaseGEffect();

protected:

	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnSphereOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	

	//~ Components for potions
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> PotionBody;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> PotionCollisionComponent;

	//~ GameplayEffects
	UPROPERTY(EditAnywhere, Category="Custom")
	TSubclassOf<UGameplayEffect> PotionEffect;
};
