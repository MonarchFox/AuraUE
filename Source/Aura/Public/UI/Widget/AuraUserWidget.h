// Coded By MonarchFox

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraUserWidget.generated.h"


/**
 * @class UAuraUserWidget
 * @brief A user widget class for Aura project.
 *
 * This class is a user widget that provides visual data and functions for Aura project.
 */

class UAuraWidgetController;

UCLASS()
class AURA_API UAuraUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	//~ Data
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UAuraWidgetController> WidgetController;

	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UAuraWidgetController* InWidgetController);
	
protected:
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
};
