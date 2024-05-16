// Coded By MonarchFox


#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "UI/HUD/AuraHUD.h"


UOverlayWidgetController* UAuraAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	if (const APlayerController* PC =  UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (const AAuraHUD* AuraHUD = Cast<AAuraHUD>(PC->GetHUD()))
		{
			if (!AuraHUD->GetOverlayWidgetController())
				GEngine->AddOnScreenDebugMessage(-1, 60, FColor::Emerald, TEXT("Set Overlay Data in AuraAbilitySystemLibrary"));

			return AuraHUD->GetOverlayWidgetController();
		}
	}
	return nullptr;
}

UAttributeMenuWidgetController* UAuraAbilitySystemLibrary::GetAttributeMenuWidgetController(
	const UObject* WorldContextObject)
{
	if (const APlayerController* PC =  UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (const AAuraHUD* AuraHUD = Cast<AAuraHUD>(PC->GetHUD()))
		{
			if (!AuraHUD->GetOverlayWidgetController())
				GEngine->AddOnScreenDebugMessage(-1, 60, FColor::Emerald, TEXT("Set Attribute Menu Data in AuraAbilitySystemLibrary"));

			return AuraHUD->GetAttributeMenuWidgetController();
		}
	}
	return nullptr;
}
