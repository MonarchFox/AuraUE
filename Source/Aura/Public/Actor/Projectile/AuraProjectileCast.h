// Coded By @niffo.dev

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AuraProjectileCast.generated.h"

class USphereComponent;

/**
 *
 *	Responsible for Casting Vfx for ensuing spell
 * 
 */

UCLASS()
class AURA_API AAuraProjectileCast : public AActor
{
	GENERATED_BODY()
	
public:	
	AAuraProjectileCast();

protected:
	virtual void BeginPlay() override;

	//~ Construction
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> SphereComponent;
};
