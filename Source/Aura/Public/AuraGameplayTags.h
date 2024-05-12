// Coded By MonarchFox

#pragma once

#include "CoreMinimal.h"
#include <mutex>

/**
 *		Singleton Object for native Gameplay Tags
 */
class AURA_API FAuraGameplayTags
{

	//~ Singleton Object
	static FAuraGameplayTags* GameplayTags;
	static std::mutex Mutex;
	
	FAuraGameplayTags() = default;

public:
	~FAuraGameplayTags();

	static const FAuraGameplayTags& Get();
	static void InitNativeGameplayTags();
};
