// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PickableComponent.h"
#include "TTGameMode.generated.h"

USTRUCT(BlueprintType)
struct FElementalDefinition
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Bitmask, BitmaskEnum = "EElementFlags"))
	uint8 ElementType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UMaterialInstanceConstant* Material;
};

UCLASS(minimalapi)
class ATTGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATTGameMode();

	UPROPERTY()
	TArray<UPickableComponent*> PickableComponents;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FElementalDefinition> ElementalDefinitions;

	UFUNCTION(BlueprintCallable)
	const FElementalDefinition& GetElementalDefinition(UPARAM(meta = (Bitmask, BitmaskEnum = EElementFlags)) uint8 elementType);
};



