// Copyright Pixel Grimoire

#pragma once

#include "CoreMinimal.h"
#include "AuraInputConfig.h"
#include "EnhancedInputComponent.h"
#include "AuraInputComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class AURA_API UAuraInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	// Types for functions when Pressed / Released / Held
	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
	void BindAbilityActions(const UAuraInputConfig* InputConfig, UserClass* UserObject, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc);
};

template <class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
void UAuraInputComponent::BindAbilityActions(const UAuraInputConfig* InputConfig, UserClass* UserObject,
	PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc)
{
	check(InputConfig)

	for(const FAuraInputAction& Action : InputConfig->AbilityInputActions)
	{
		if(Action.InputAction && Action.InputTag.IsValid())
		{
			// Binds the Func to the Input Action with the TriggerEvent, passing along the GameplayTags as params to Func
			if(PressedFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Started, UserObject, PressedFunc, Action.InputTag);
			}
			if(ReleasedFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Completed, UserObject, ReleasedFunc, Action.InputTag);
			}
			if(HeldFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Triggered, UserObject, HeldFunc, Action.InputTag);	
			}
		}
	}
}
