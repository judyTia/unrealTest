// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "PickableComponent.generated.h"

/**
 * 
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class TECHNICALTEST_API UPickableComponent : public USphereComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	float PickedUpApproachFactor = 0.999f;

	UPROPERTY(EditDefaultsOnly)
	float OffsetForDrop = 60.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bCanBePickedUp = true;

	UPickableComponent();

	virtual void BeginPlay() override;
	virtual void EndPlay(EEndPlayReason::Type endPlayReason) override;

	virtual void TickComponent(float deltaTime, enum ELevelTick tickType, FActorComponentTickFunction *thisTickFunction);

	void DisablePhysics();
	void EnablePhysics();

public:
	UFUNCTION(BlueprintNativeEvent)
	void OnPickup(class ATTCharacter* pawn);
	virtual void OnPickup_Implementation(class ATTCharacter* pawn);

	UFUNCTION(BlueprintNativeEvent)
	void OnDrop(class ATTCharacter* pawn);
	virtual void OnDrop_Implementation(class ATTCharacter* pawn);

	UPROPERTY(transient)
	class ATTCharacter* PickedUpBy = nullptr;

private:
	FTransform RelativePickedUpTransform;
};
