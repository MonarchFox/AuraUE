// Coded By MonarchFox

#pragma once

#include "CoreMinimal.h"
#include "AuraWidgetController.generated.h"


class UAttributeSet;
class UAbilitySystemComponent;
class APlayerState;


/**
 * @class FWidgetControllerParam
 * @brief Represents a widget controller that holds references to various components.
 * @details This struct is used to store references to a player controller, player state, ability system component, and attribute set.
 *
 * @property PlayerController The player controller associated with the widget controller.
 * @property PlayerState The player state associated with the widget controller.
 * @property AbilitySystemComponent The ability system component associated with the widget controller.
 * @property AttributeSet The attribute set associated with the widget controller.
 */
USTRUCT(Blueprintable)
struct FWidgetControllerParam
{
	GENERATED_BODY()

	FWidgetControllerParam() {}

	FWidgetControllerParam(APlayerController* PlayerController, APlayerState* PlayerState,
		UAbilitySystemComponent* AbilitySystemComponent, UAttributeSet* AttributeSet):
	PlayerController(PlayerController), PlayerState(PlayerState),
	AbilitySystemComponent(AbilitySystemComponent), AttributeSet(AttributeSet) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerController> PlayerController = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerState> PlayerState = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAttributeSet> AttributeSet = nullptr;
};

/**
 * @class UAuraWidgetController
 * @brief Represents a widget controller that holds references to various components.
 * @details This class is used to store references to a player controller, player state, ability system component, and attribute set.
 *
 * @method SetWidgetController Sets the widget controller with the given values.
 * @param WidgetController The widget controller struct containing the references to the components.
 * @return void
 *
 * @property PlayerController The player controller associated with the widget controller.
 * @property PlayerState The player state associated with the widget controller.
 * @property AbilitySystemComponent The ability system component associated with the widget controller.
 * @property AttributeSet The attribute set associated with the widget controller.
 *
 * @property PlayerController The player controller associated with the widget controller.
 * @property PlayerState The player state associated with the widget controller.
 * @property AbilitySystemComponent The ability system component associated with the widget controller.
 * @property AttributeSet The attribute set associated with the widget controller.
 */
UCLASS()
class AURA_API UAuraWidgetController : public UObject
{
	GENERATED_BODY()
	FString WidgetControllerName = "Default";

public:
	
	UFUNCTION(BlueprintCallable)
	void SetWidgetControllerParam(const FWidgetControllerParam& WidgetController);
	virtual void BroadcastInitialValues();
	virtual void BindCallbacksToDependencies();

	FORCEINLINE FString GetWidgetControllerName() const { return WidgetControllerName; }
	FORCEINLINE void SetWidgetControllerName(FString NewName)
	{ WidgetControllerName = NewName; }
	
protected:
	
	// Section Data Broadcast 
	UPROPERTY(BlueprintReadOnly, Category="Widget Controller")
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly, Category="Widget Controller")
	TObjectPtr<APlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly, Category="Widget Controller")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category="Widget Controller")
	TObjectPtr<UAttributeSet> AttributeSet;

	// End Data Broadcast
};
