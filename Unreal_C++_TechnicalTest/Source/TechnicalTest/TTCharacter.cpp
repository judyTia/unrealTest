// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "TechnicalTest.h"

#include "TTCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

#include "TTGameMode.h"
#include "PickableComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// ATTCharacter

ATTCharacter::ATTCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Default offset from the character location for picked up item to stay
	PickupOffset = FVector(100.0f, 0.0f, 10.0f);
}

void ATTCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
}

//////////////////////////////////////////////////////////////////////////
// Input

void ATTCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind fire event
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ATTCharacter::OnInteractStarted);
	PlayerInputComponent->BindAction("Interact", IE_Released, this, &ATTCharacter::OnInteractStopped);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &ATTCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATTCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ATTCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ATTCharacter::LookUpAtRate);
}

void ATTCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void ATTCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void ATTCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ATTCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

bool ATTCharacter::IsLookingAtPickable() const
{
	return !IsHoldingPickable() && PickableInFocus != nullptr;
}

bool ATTCharacter::IsHoldingPickable() const
{
	return PickableInHand != nullptr;
}

void ATTCharacter::ForceDropPickable()
{
	if (PickableInHand != nullptr)
	{
		PickableInHand->OnDrop(this);
	}
	PickableInHand = nullptr;
}

void ATTCharacter::OnInteractStarted()
{
	bInteractPressed = true;
	bInteractHeld = true;
}

void ATTCharacter::OnInteractStopped()
{
	bInteractHeld = false;
	bInteractReleased = true;
}

void ATTCharacter::UpdateInteraction()
{
	FVector eyeLocation = FirstPersonCameraComponent->GetComponentLocation();
	FVector eyeForward = FirstPersonCameraComponent->GetComponentQuat().GetForwardVector();

	ATTGameMode* gameMode = Utils::GetGameMode();
	if (gameMode != nullptr)
	{
		PickableInFocus = nullptr;

		if (!IsHoldingPickable())
		{
			// Technical Test
			// Task #1

			// Assign the pickable that this character is currently looking at to PickableInFocus, for simplicity you can ignore collisions

			// All PickableComponent can be found here: gameMode->PickableComponents
			// PickableComponents can be enabled/disabled with bCanBePickedUp
			// The make pickup distance is: MaxPickupDistance

			//PickableInFocus = ???
		}

		if (bInteractPressed)
		{
			PickableInHand = PickableInFocus;
			if (PickableInHand != nullptr)
			{
				PickableInHand->OnPickup(this);
			}
		}

		if (bInteractReleased)
		{
			ForceDropPickable();
		}
	}
}

void ATTCharacter::Tick(float deltaTime)
{
	UpdateInteraction();

	bInteractPressed = false;
	bInteractReleased = false;
}
