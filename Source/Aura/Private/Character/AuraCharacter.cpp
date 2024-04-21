// Coded By MonarchFox


#include "Character/AuraCharacter.h"

#include "AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/AuraPlayerState.h"


AAuraCharacter::AAuraCharacter()
{
	/** !Defaults */
	PrimaryActorTick.bCanEverTick = true;

	// + Character Movement Defaults
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// + Controller Defaults
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	// + Camera Component Defaults

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArmComponent->SetupAttachment(GetRootComponent());

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	CameraComponent->bUsePawnControlRotation = false;
	
}

/**
 * @brief Possesses the character with the given controller and initializes the ability actor information.
 *
 * This method is called when the character is possessed by a controller.
 * It initializes the ability actor information for the server.
 *
 * @param NewController The controller that possesses the character.
 *
 * @note This method is called internally and should not be called directly.
 */
void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init Ability Actor info for the server
	InitAbilityActorInfo();
}

/**
 * @brief Called when the player state of the character changes.
 *
 * This method is called when the player state of the character changes
 * on the server and needs to be replicated to clients. It calls the
 * parent OnRep_PlayerState() method and then initializes the ability
 * actor information for the client by calling InitAbilityActorInfo().
 *
 * @note This method is called internally and should not be called directly.
 */
void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Init Ability Actor info for the client
	InitAbilityActorInfo();
}

/**
 * @brief Initializes the ability actor information for the character.
 *
 * This method is called internally when the character is possessed by a controller.
 * It retrieves the AuraPlayerState and initializes the ability actor information
 * using the GetAbilitySystemComponent() method of AuraPlayerState.
 *
 * @note This method should not be called directly.
 */
void AAuraCharacter::InitAbilityActorInfo()
{
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);

	AuraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AuraPlayerState, this);
	AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
	AttributeSet = AuraPlayerState->GetAttributeSet();
}
