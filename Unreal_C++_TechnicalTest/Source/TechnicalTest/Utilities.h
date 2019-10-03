
#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"

#if WITH_EDITOR
#include "Editor.h"
#endif

#if UE_BUILD_SHIPPING
#define TWEAKABLE const
#else
#define TWEAKABLE static
#endif

class UWorld;

struct Utils
{
	static UWorld* GetGameWorld();
	static class ATTGameMode* GetGameMode();

	static int GetEnumCount(FName enumName);

	template<class T> FORCEINLINE static T Approach(const T& current, const T& target, float coeff, float deltaTime)
	{
		return target + (current - target) * FMath::Pow((1.0f - coeff), deltaTime);
	}

	static void PrintToScreen(const FString& string);
};