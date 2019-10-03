// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "TechnicalTest.h"
#include "GameFramework/HUD.h"
#include "TTHud.generated.h"

UCLASS()
class ATTHud : public AHUD
{
	GENERATED_BODY()

public:
	ATTHud();

	virtual void Tick(float deltaTime) override;

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* DefaultCrosshairTex;
	class UTexture2D* CanPickupCrosshairTex;
	class UTexture2D* HoldingCrosshairTex;

	float SmoothActionRatio = 0.0f;
};

