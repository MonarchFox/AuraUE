// Coded By MonarchFox


#include "UI/WidgetController/AuraWidgetController.h"



void UAuraWidgetController::SetWidgetControllerParam(const FWidgetControllerParam& WidgetController)
{
	PlayerController = WidgetController.PlayerController;
	PlayerState = WidgetController.PlayerState;
	AbilitySystemComponent = WidgetController.AbilitySystemComponent;
	AttributeSet = WidgetController.AttributeSet;
}

void UAuraWidgetController::BroadcastInitialValues()
{
	
}

void UAuraWidgetController::BindCallbacksToDependencies()
{
	
}
