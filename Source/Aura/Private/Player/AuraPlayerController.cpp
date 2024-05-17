// Coded By MonarchFox

#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h" 
#include "Input/AuraInputComponent.h"
#include "Interaction/EnemyInterface.h"
#include "UI/HUD/AuraHUD.h"
#include "UI/Widget/AuraUserWidget.h"


AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	InitController();
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

	UAuraInputComponent* AuraInputComponent = CastChecked<UAuraInputComponent>(InputComponent);

	//~ Movement Bindings
	AuraInputComponent->BindAction(MoveInputAction, ETriggerEvent::Triggered,
		this, &AAuraPlayerController::MoveAction);
	AuraInputComponent->BindAction(MouseInputAction, ETriggerEvent::Triggered, this,
		&AAuraPlayerController::MouseAction);

	//~ Widget Bindings
	AuraInputComponent->BindAction(AttributeMenuInputAction, ETriggerEvent::Started,
		this, &AAuraPlayerController::AttributeMenuAction);

	//~ Abilities Bindings
	AuraInputComponent->BindAbilityActions(AbilityInputConfig, this,
											&AAuraPlayerController::AbilityInputTagPressed,
											&AAuraPlayerController::AbilityInputTagReleased,
											&AAuraPlayerController::AbilityInputTagHeld);
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

void AAuraPlayerController::AttributeMenuAction(const FInputActionValue& Action)
{
	const bool Value  = Action.Get<bool>();
	if (!Value) return;

	bShowMouseCursor = !bShowMouseCursor;

	if (const AAuraHUD* AuraHUD = Cast<AAuraHUD>(GetHUD()))
	{
		if (bShowMouseCursor)
		{
			AuraHUD->SetAttributeMenuVisibility(ESlateVisibility::Visible);
			
			//~ Configuring Mouse Behaviour
			FInputModeGameAndUI InputModeData;
			DefaultMouseCursor = EMouseCursor::Default;
			InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			InputModeData.SetHideCursorDuringCapture(false);
			SetInputMode(InputModeData);
		}
		else
		{
			AuraHUD->SetAttributeMenuVisibility(ESlateVisibility::Hidden);

			//~ Resetting mouse behaviour
			FInputModeGameOnly InputModeData;
			InputModeData.SetConsumeCaptureMouseDown(false);
			SetInputMode(InputModeData);
		}
	}
}

void AAuraPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	if (!GetAuraAbilitySystemComponent()) return;
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, TEXT("Pressed"));
}

void AAuraPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (!GetAuraAbilitySystemComponent()) return;
	GetAuraAbilitySystemComponent()->AbilityInputTagHeld(InputTag);
}

void AAuraPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (!GetAuraAbilitySystemComponent()) return;
	GetAuraAbilitySystemComponent()->AbilityInputTagReleased(InputTag);
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
