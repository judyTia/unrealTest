// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ElementalComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnElementChangedEvent);

UENUM(BlueprintType)
enum class EElementFlags : uint8
{
	Air,
	Earth,
	Fire,
	Water
};
ENUM_CLASS_FLAGS(EElementFlags);

/**
 * 
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class TECHNICALTEST_API UElementalComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Bitmask, BitmaskEnum = "EElementFlags"))
	uint8 ElementType;

	UFUNCTION(BlueprintCallable)
	void SetElement(UPARAM(meta = (Bitmask, BitmaskEnum = EElementFlags)) uint8 elementTypeValue);

	UFUNCTION(BlueprintCallable)
	void AddElements(UPARAM(meta = (Bitmask, BitmaskEnum = EElementFlags)) uint8 elementTypeValue);

	UFUNCTION(BlueprintCallable)
	void RemoveElements(UPARAM(meta = (Bitmask, BitmaskEnum = EElementFlags)) uint8 elementTypeValue);

	int GetElementCount() const;

	UFUNCTION(BlueprintCallable)
	bool IsSplittable() const;

	UFUNCTION(BlueprintCallable)
	TArray<uint8> SplitElement(int splitCount);

	// Return the merged element at index 0, then a copy of the array with what elements are left
	UFUNCTION(BlueprintCallable)
	static TArray<uint8> MergeElement(TArray<UElementalComponent*> elements);

	UPROPERTY(BlueprintAssignable)
	FOnElementChangedEvent OnElementChangedEvent;
};
