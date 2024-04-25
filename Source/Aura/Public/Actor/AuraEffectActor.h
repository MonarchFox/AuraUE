// Coded By MonarchFox

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "AuraEffectActor.generated.h"


enum class EGameplayEffectDurationType: uint8;
class UGameplayEffect;

UENUM(BlueprintType)
enum class EEffectApplicationPolicy
{
	/** This effect applies On Overlap */
	ApplyOnOverlap,
	/** This effect applies End Overlap */
	ApplyOnEndOverlap,
	/** This effect does not apply */
	DoNotApply,
};

UENUM(BlueprintType)
enum class EEffectRemovalPolicy
{
	/** This effect get removed on end overlap */
	RemoveOnEndOverlap,
	/** This effect is Persistent */
	Persistent,
};

/**
 * \class AAuraEffectActor
 * \brief A base class for actors implementing gameplay effect handling.
 *
 * The `AAuraEffectActor` class provides functionality for applying and managing gameplay effects on target actors.
 * It serves as a base class for other aura-related actors.
 */
UCLASS()
class AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()

	//? Meta Information
	UPROPERTY(EditAnywhere, Category="Custom", meta=(AllowPrivateAccess="true"))
	TSubclassOf<UGameplayEffect> GameplayEffectObject;
	
	UPROPERTY(EditAnywhere, Category="Custom", meta=(AllowPrivateAccess="true"))
	EEffectApplicationPolicy EffectApplicationPolicy = EEffectApplicationPolicy::ApplyOnOverlap;

	UPROPERTY(EditAnywhere, Category="Custom", meta=(AllowPrivateAccess="true"))
	EEffectRemovalPolicy EffectRemovalPolicy = EEffectRemovalPolicy::Persistent;
	
	UPROPERTY(EditAnywhere, Category="Custom", meta=(AllowPrivateAccess="true"))
	bool bDestroyOnEffectRemoval = false;

	UPROPERTY(VisibleAnywhere)
	EGameplayEffectDurationType GameplayEffectDurationType;

	UPROPERTY(VisibleAnywhere)
	TMap<UAbilitySystemComponent*, FActiveGameplayEffectHandle> ActiveEffectHandleMap;

public:	
	AAuraEffectActor();
	virtual void BeginPlay() override;

protected:

	// Section Gameplay Effects
	UFUNCTION(BlueprintCallable)
	virtual void ApplyEffectToTarget(AActor* Target, TSubclassOf<UGameplayEffect> GameplayEffectClass);

	UFUNCTION(BlueprintCallable)
	virtual void GameplayEffectOnOverlap(AActor* Target);

	UFUNCTION(BlueprintCallable)
	virtual void GameplayEffectOnEndOverlap(AActor* Target);
	
	// End Gameplay Effects 

	//? Meta Information Setters and Getters
	FORCEINLINE TSubclassOf<UGameplayEffect> GetGameplayEffectObject() const { return GameplayEffectObject; }
	
	FORCEINLINE void SetEffectApplicationPolicy(const EEffectApplicationPolicy Policy) { EffectApplicationPolicy = Policy; }
	FORCEINLINE EEffectApplicationPolicy GetEffectApplicationPolicy() const { return EffectApplicationPolicy; }

	FORCEINLINE void SetEffectRemovalPolicy(const EEffectRemovalPolicy Policy) { EffectRemovalPolicy = Policy; }
	FORCEINLINE EEffectRemovalPolicy GetEffectRemovalPolicy() const { return EffectRemovalPolicy; }

	FORCEINLINE void IsDestroyOnEffectRemoval(const bool Policy) { bDestroyOnEffectRemoval = Policy; }
	FORCEINLINE bool IsDestroyOnEffectRemoval() const { return bDestroyOnEffectRemoval; }

	FORCEINLINE void SetGameplayEffectDurationType(const EGameplayEffectDurationType Type) { GameplayEffectDurationType = Type; }
	FORCEINLINE EGameplayEffectDurationType GetGameplayEffectDurationType() const { return GameplayEffectDurationType; }
};
