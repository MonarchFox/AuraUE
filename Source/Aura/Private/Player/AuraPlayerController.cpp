// Coded By MonarchFox


#include "Player/AuraPlayerController.h"

#include "EnhancedInputSubsystems.h" 
#include "EnhancedInputComponent.h" 
#include "Interaction/EnemyInterface.h"


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

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(AuraInputContext, 0);
	}
}

void AAuraPlayerController::InitCursor()
{
	// !Initialize Controller Mouse Cursor
	// TODO: Add Aiming System
	// bShowMouseCursor = true;
	//DefaultMouseCursor = EMouseCursor::Default;
	
	//FInputModeGameAndUI InputModeData;
	// InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	//InputModeData.SetHideCursorDuringCapture(false);
	
	//SetInputMode(InputModeData);
}

// End Initial Setups

// Section Input Setups

void AAuraPlayerController::SetupInputComponent()
{
	// !Binds Inputs
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent =
		CastChecked<UEnhancedInputComponent>(InputComponent);


	EnhancedInputComponent->BindAction(MoveInputAction, ETriggerEvent::Triggered,
		this, &AAuraPlayerController::MoveAction);
	EnhancedInputComponent->BindAction(MouseInputAction, ETriggerEvent::Triggered, this,
		&AAuraPlayerController::MouseAction);
	
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

void AAuraPlayerController::MouseAction(const FInputActionValue& Action)
{
	const FVector2d LookInput = Action.Get<FVector2d>();
	
	AddYawInput(LookInput.X);
	AddPitchInput(LookInput.Y);
}

// End Input Setups

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

// Section Enemy Interface


void AAuraPlayerController::CursorTrace()
{
	// !Uses EnemyInterface HighLight Effects on hovering
	
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);

	if (!CursorHit.bBlockingHit) return;
	
	StepActor(CursorHit);
	PerformHighlights(CursorHit);
}

void AAuraPlayerController::StepActor(const FHitResult& CHit)
{
	// !Step Forward Actor History
	LastActor = CurrentActor;
	CurrentActor  = Cast<IEnemyInterface>(CHit.GetActor());
}

void AAuraPlayerController::PerformHighlights(const FHitResult& CHit) const
{
	// !Implements Highlight and UnHighlight Conditions for Actor
	
    if (!LastActor && CurrentActor) CurrentActor->HighLightActor();
    if (LastActor && !CurrentActor) LastActor->UnHighLightActor();
    if (LastActor && CurrentActor && LastActor != CurrentActor)
    {
    	LastActor->UnHighLightActor();
    	CurrentActor->HighLightActor();
    }
}

// End Enemy Interface
