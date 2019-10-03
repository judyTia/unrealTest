// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "PickableMagnetComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMagnetAction, UPickableComponent*, pickable);

/**
 * 
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class TECHNICALTEST_API UPickableMagnetComponent : public USphereComponent
{
	GENERATED_BODY()

	UPickableMagnetComponent();

public:
	virtual void TickComponent(float deltaTime, enum ELevelTick tickType, FActorComponentTickFunction *thisTickFunction);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bActive = true;

	UPROPERTY(transient, BlueprintReadOnly)
	class UPickableComponent* CurrentPickable;

	UPROPERTY(BlueprintAssignable)
	FOnMagnetAction OnDropEvent;

	UPROPERTY(BlueprintAssignable)
	FOnMagnetAction OnPickupEvent;

	UFUNCTION(BlueprintCallable)
	bool IsAvailable() const;

	UFUNCTION(BlueprintCallable)
	void AttachPickable(class UPickableComponent* pickable);

	UFUNCTION(BlueprintCallable)
	void DetachPickable(class UPickableComponent* pickable);
};
