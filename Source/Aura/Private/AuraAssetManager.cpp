// Coded By MonarchFox

#include "AuraAssetManager.h"
#include "AuraGameplayTags.h"
#include "AbilitySystemGlobals.h" 


UAuraAssetManager& UAuraAssetManager::Get()
{
	checkf(GEngine, TEXT("Cant Load Asset Manager in AuraAsset Manager"));

	UAuraAssetManager* AuraAssetManager = Cast<UAuraAssetManager>(GEngine->AssetManager);
	return *AuraAssetManager;
}

void UAuraAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	FAuraGameplayTags::InitNativeGameplayTags();

	//~ Required to use target data
	UAbilitySystemGlobals::Get().InitGlobalData();
}
