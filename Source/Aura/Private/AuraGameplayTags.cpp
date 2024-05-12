// Coded By MonarchFox


#include "AuraGameplayTags.h"
#include "GameplayTagsManager.h"

//~ Static Objects
FAuraGameplayTags* FAuraGameplayTags::GameplayTags = nullptr;
std::mutex FAuraGameplayTags::Mutex;


FAuraGameplayTags::~FAuraGameplayTags()
{
	delete GameplayTags;
}

const FAuraGameplayTags& FAuraGameplayTags::Get()
{
	//~ Double Check Tread Safe
	if (GameplayTags == nullptr)
	{
		std::lock_guard<std::mutex> Lock(Mutex);
		if (!GameplayTags) GameplayTags = new FAuraGameplayTags();
	}
	return *GameplayTags;
}

void FAuraGameplayTags::InitNativeGameplayTags()
{
	UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.Armor"),
		FString("Reduce Physical Damage Taken"));
}
