// Coded By MonarchFox

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AuraInputConfig.generated.h"

//? Forward Declarations
class UInputAction;

/** AuraInput Action Key Map Data */
USTRUCT(BlueprintType)
struct FAuraInputAction
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	const UInputAction* InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag = FGameplayTag();
};

/**
 *		Stores Aura Input Bindings
 */
UCLASS()
class AURA_API UAuraInputConfig : public UDataAsset
{
	GENERATED_BODY()
	
public:

	//? Getters
	const UInputAction* FindAbilityInputAction(const FGameplayTag& InputTag,
		const bool bLogNotFound=false) const;
	
	//~ Stores Input Bindings
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	TArray<FAuraInputAction> AbilityInputActionStorage;
};
