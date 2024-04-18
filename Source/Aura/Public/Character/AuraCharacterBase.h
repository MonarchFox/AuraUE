// Coded By MonarchFox

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AuraCharacterBase.generated.h"

UCLASS(Abstract, NotBlueprintable)
class AURA_API AAuraCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AAuraCharacterBase();

protected:
	virtual void BeginPlay() override;

	// Region StaticMeshComponent References
	
	UPROPERTY(EditAnywhere, Category="Combat")
	TObjectPtr<USkeletalMeshComponent> WeaponComponent;

	UPROPERTY(EditAnywhere, Category="Combat")
	FName WeaponComponentSocketName { "WeaponHandSocket" };

	// End Region
};
