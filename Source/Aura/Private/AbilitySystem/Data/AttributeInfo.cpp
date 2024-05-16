// Coded By MonarchFox

#include "AbilitySystem/Data/AttributeInfo.h"

FAuraAttributeInfo UAttributeInfo::FindAttributeInfoForTag(	const FGameplayTag& AttributeTag,
															const bool bLogNotFound) const
{
	for(const FAuraAttributeInfo& TagInfo: AttributeInformation)
		if (TagInfo.AttributeTag == AttributeTag) return TagInfo;
	
	if (bLogNotFound)
		UE_LOG(LogTemp, Error, TEXT("Cant Find AttributeTag inside AttributeInformations"));
	
	return FAuraAttributeInfo();
}
