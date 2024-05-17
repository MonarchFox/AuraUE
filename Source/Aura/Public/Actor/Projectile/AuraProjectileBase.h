// Coded By MonarchFox

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AuraProjectileBase.generated.h"


//? Default Value
#define PROJECTILE_INITIAL_SPEED 550.f
#define PROJECTILE_MAX_SPEED 600.f
#define PROJECTILE_GRAVITY_SCALE 0

//? Forward Declarations
class USphereComponent;
class UProjectileMovementComponent;


UCLASS()
class AURA_API AAuraProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AAuraProjectileBase();

protected:
	virtual void BeginPlay() override;

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

public:

	//? Getters and setters
	//~ Structure Getters (accepts no Setters for this category)
	FORCEINLINE UProjectileMovementComponent* GetProjectileMovementComponent() const { return ProjectileMovementComponent; }
};