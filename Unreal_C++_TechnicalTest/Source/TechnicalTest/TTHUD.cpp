// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "TTHud.h"
#include "Engine/Canvas.h"
#include "Engine/Texture2D.h"
#include "TextureResource.h"
#include "CanvasItem.h"
#include "UObject/ConstructorHelpers.h"
#include "TTCharacter.h"

// Technical Test
// Task #3

// Convert ATTHud behavior to a Blueprint Widget (WidgetBlueprint'/Game/TechnicalTest/Blueprints/CharacterHUD.CharacterHUD')
// Convert the current cursor behavior in blueprint
// Elemental information is valid when looking at or holding a pickable with the ElementalComponent
// No elemental information should be visible when it doesn't apply
// When elemental information apply all base should be visible, but only the appropriate elemental overlay should be visible

ATTHud::ATTHud()
{
	// Set the crosshair texture
	static ConstructorHelpers::FObjectFinder<UTexture2D> DefaultCrosshairTexbj(TEXT("Texture2D'/Game/TechnicalTest/Textures/UI/Default.Default'"));
	DefaultCrosshairTex = DefaultCrosshairTexbj.Object;

	static ConstructorHelpers::FObjectFinder<UTexture2D> CanPickupCrosshairTexObj(TEXT("Texture2D'/Game/TechnicalTest/Textures/UI/CanGrabCrosshair.CanGrabCrosshair'"));
	CanPickupCrosshairTex = CanPickupCrosshairTexObj.Object;

	static ConstructorHelpers::FObjectFinder<UTexture2D> HoldingCrosshairTexObj(TEXT("Texture2D'/Game/TechnicalTest/Textures/UI/GrabbedCrosshair.GrabbedCrosshair'"));
	HoldingCrosshairTex = HoldingCrosshairTexObj.Object;
}

void ATTHud::Tick(float deltaTime)
{
	ATTCharacter* ttCharacter = Cast<ATTCharacter>(GetOwningPawn());

	if (ttCharacter != nullptr)
	{
		float desiredActionRatio = ttCharacter->IsLookingAtPickable() || ttCharacter->IsHoldingPickable();

		TWEAKABLE float AppproachFactor = 0.99999f;
		SmoothActionRatio = Utils::Approach(SmoothActionRatio, desiredActionRatio, AppproachFactor, deltaTime);
	}
}

void ATTHud::DrawHUD()
{
	Super::DrawHUD();

	// Draw very simple crosshair

	// find center of the Canvas
	const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

	// offset by half the texture's dimensions so that the center of the texture aligns with the center of the Canvas
	const FVector2D CrosshairDrawPosition( (Center.X - 8),
										   (Center.Y) - 8);

	

	// draw the crosshair
	FCanvasTileItem BaseTileItem( CrosshairDrawPosition, DefaultCrosshairTex->Resource, FLinearColor(1.0f, 1.0f, 1.0f, 1.0f - SmoothActionRatio));
	BaseTileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(BaseTileItem);

	ATTCharacter* ttCharacter = Cast<ATTCharacter>(GetOwningPawn());

	if (ttCharacter != nullptr)
	{
		UTexture2D* actionCrosshair = ttCharacter->IsHoldingPickable() ? HoldingCrosshairTex : CanPickupCrosshairTex;

		if (actionCrosshair != nullptr)
		{
			FCanvasTileItem ActionTileItem(CrosshairDrawPosition, actionCrosshair->Resource, FLinearColor(1.0f, 1.0f, 1.0f, SmoothActionRatio));
			ActionTileItem.BlendMode = SE_BLEND_Translucent;
			Canvas->DrawItem(ActionTileItem);
		}
	}
}
