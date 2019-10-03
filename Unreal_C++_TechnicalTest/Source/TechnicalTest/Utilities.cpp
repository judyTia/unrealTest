#pragma once

#include "Utilities.h"
#include "CoreMinimal.h"
#include "Engine/World.h"
#include "TTGameMode.h"

UWorld* Utils::GetGameWorld()
{
	UWorld* theWorld = nullptr;

	for (const FWorldContext& Context : GEngine->GetWorldContexts())
	{
		UWorld* curWorld = Context.World();
		if (curWorld && curWorld->IsGameWorld()) // not sure if this is enough?
		{
#if WITH_EDITOR
			/*if (GIsEditor && GEditor->PlayWorld == curWorld)
			{
				return curWorld;
			}*/
#endif

			check(theWorld == nullptr); // Unsafe use of Utils::GetGameWorld() - more than one possible world!

			theWorld = curWorld;
		}
	}

	return theWorld;
}

ATTGameMode* Utils::GetGameMode()
{
	UWorld* world = GetGameWorld();
	if (world != nullptr)
	{
		return Cast<ATTGameMode>(world->GetAuthGameMode());
	}

	return nullptr;
}

int Utils::GetEnumCount(FName enumName)
{
	UEnum* enumClass = FindObject<UEnum>(ANY_PACKAGE, *enumName.ToString(), true);
	if (enumClass == nullptr)
	{
		return 0;
	}

	int numMembers = enumClass->NumEnums() - 1; // -1 because the metadata always includes a hidden "EnumName_MAX" value

	return numMembers;
}

void Utils::PrintToScreen(const FString& string)
{
	if (GEngine != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White, string);
	}
}