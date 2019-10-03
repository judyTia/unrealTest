// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TTCharacter.generated.h"

class UInputComponent;

UCLASS(config=Game, Blueprintable)
class ATTCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ATTCharacter();

protected:
	virtual void BeginPlay();

public:
	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent; 

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	/** Picked up actor's offset from the characters location */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Gameplay)
	FVector PickupOffset;

	/** Picked up actor's offset from the characters location */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Gameplay)
	float MaxPickupDistance = 250.0f;

	bool IsLookingAtPickable() const;
	bool IsHoldingPickable() const;

	void ForceDropPickable();

protected:

	bool bInteractPressed;
	bool bInteractHeld;
	bool bInteractReleased;

	void OnInteractStarted();
	void OnInteractStopped();

	void UpdateInteraction();

	virtual void Tick(float deltaTime) override;

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);
	
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

private:
	UPROPERTY()
	class UPickableComponent* PickableInFocus;

	UPROPERTY()
	class UPickableComponent* PickableInHand;
};

