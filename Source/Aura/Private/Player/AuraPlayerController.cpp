// Coded By MonarchFox


#include "Player/AuraPlayerController.h"

#include "EnhancedInputSubsystems.h" 
#include "EnhancedInputComponent.h" 


AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	InitController();
	InitCursor();
}

// Section Initial Setups

void AAuraPlayerController::InitController() const
{
	// !Initialize Player Controller

	check(AuraInputContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	check(Subsystem);

	Subsystem->AddMappingContext(AuraInputContext, 0);
}

void AAuraPlayerController::InitCursor()
{
	// !Initialize Controller Mouse Cursor
	
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);

	SetInputMode(InputModeData);
}

// End

// Section Input Setups

void AAuraPlayerController::SetupInputComponent()
{
	// !Binds Inputs
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent =
		CastChecked<UEnhancedInputComponent>(InputComponent);


	EnhancedInputComponent->BindAction(MoveInputAction, ETriggerEvent::Triggered,
		this, &AAuraPlayerController::MoveAction);
	
}

// Sub-Section Input Bindings

void AAuraPlayerController::MoveAction(const FInputActionValue& Action)
{
	// !Implements Player Movement With Respect to its Directions and Move Mesh forward direction towards it 

	const FVector2d ActionInput = Action.Get<FVector2d>();

	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation {0, Rotation.Yaw, 0};

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, ActionInput.Y);
		ControlledPawn->AddMovementInput(RightDirection, ActionInput.X);
	}
}

// End
