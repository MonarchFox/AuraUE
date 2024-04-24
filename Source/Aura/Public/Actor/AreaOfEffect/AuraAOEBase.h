// Coded By MonarchFox

#pragma once

#include "CoreMinimal.h"
#include "Actor/AuraEffectActor.h"
#include "AuraAOEBase.generated.h"


class USphereComponent;
class UNiagaraComponent;

/**
 * 
 */
UCLASS()
class AURA_API AAuraAOEBase : public AAuraEffectActor
{
	GENERATED_BODY()

	//? Meta Information
	UPROPERTY(EditAnywhere, Category="Custom", meta=(AllowPrivateAccess="true"))
	TSubclassOf<UGameplayEffect> AOEGameplayEffect;

	UPROPERTY(EditAnywhere, Category="Custom", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UNiagaraComponent> NiagaraComponent;

public:
	AAuraAOEBase();

	UFUNCTION()
	void OnComponentOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//? Getters
	FORCEINLINE TSubclassOf<UGameplayEffect> GetAOEGameplayEffect() const { return AOEGameplayEffect; }
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> SceneComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> SphereComponent;
};
