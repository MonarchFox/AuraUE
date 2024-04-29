// Coded By MonarchFox

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "OverlayWidgetController.generated.h"

//? Forward Declarations
class UAuraUserWidget;
class UAbilityInfo;
class UAuraAbilitySystemComponent;


//? Custom Structures
USTRUCT(BlueprintType)
struct FUIWidgetRow: public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag MessageTag = FGameplayTag();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Message = FText();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UAuraUserWidget> MessageWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Image = nullptr;
};

//? Delegations
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedSignature, float, NewValue);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMessageWidgetRowSignature, FUIWidgetRow, Row);


/**
 * @class UOverlayWidgetController
 * @brief An overlay widget controller class for Aura HUD.
 *
 * This class is responsible for controlling the overlay widget in Aura HUD.
 */
UCLASS(BlueprintType, Blueprintable)
class AURA_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()

public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	// Section Delegations

	// + Health Attribute
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChangedSignature OnMaxHealthChanged;

	// + Mana Attribute
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChangedSignature OnManaChanged;
	
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChangedSignature OnMaxManaChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Message")
	FMessageWidgetRowSignature MessageDelegate;

	// Section End


protected:

	//? Meta Information

	UPROPERTY(EditDefaultsOnly, Category="Custom", meta=(AllowPrivateAccess="true"), BlueprintReadOnly)
	TObjectPtr<UDataTable> MessageWidgetDataTable;
	
	//~ Template
	template<typename T>
	static T* GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag);

	//~ Delegate Template
	template<class T>
	static void AttributeBroadcast(const T& Data, FOnAttributeChangedSignature& DelegateAttribute);
	
	void BroadcastWidgetRow(const FGameplayTagContainer& AssetTags, const FName ParentName) const;
	
	//? Meta Information Getters and Setters
	FORCEINLINE TObjectPtr<UDataTable> GetMessageWidgetDataTable() const { return MessageWidgetDataTable; }
	
};

template <typename T>
T* UOverlayWidgetController::GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag)
{
	return DataTable->FindRow<T>(Tag.GetTagName(), TEXT(""));
}

template <class T>
void UOverlayWidgetController::AttributeBroadcast(const T& Data, FOnAttributeChangedSignature& DelegateAttribute)
{
	DelegateAttribute.Broadcast(Data.NewValue);
}
