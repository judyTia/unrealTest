// Fill out your copyright notice in the Description page of Project Settings.

#include "TechnicalTest.h"
#include "ElementalComponent.h"

void UElementalComponent::SetElement(uint8 elementType)
{
	ElementType = elementType;

	OnElementChangedEvent.Broadcast();
}

void UElementalComponent::AddElements(uint8 elementType)
{
	// Technical Test
	// Task #2.1

	// Add a set of ElementType flags to ElementType
	// Elements are bit exclusive that are defines like this
	// EElementFlags::Air	= 0x01
	// EElementFlags::Earth = 0x02
	// EElementFlags::Fire	= 0x04
	// EElementFlags::Water = 0x08
}

void UElementalComponent::RemoveElements(uint8 elementType)
{
	// Technical Test
	// Task #2.2

	// Remove a set of ElementType flags to ElementType
}

int UElementalComponent::GetElementCount() const
{
	int numberOfElements = 0;

	// Technical Test
	// Task #2.3

	// Returns a count of bit in ElementType

	return numberOfElements;
}

bool UElementalComponent::UElementalComponent::IsSplittable() const
{
	return GetElementCount() > 1;
}

TArray<uint8> UElementalComponent::SplitElement(int splitCount)
{
	TArray<uint8> splittedElements;

	// Technical Test
	// Task #2.4

	// Take ElementType and split it in the specified amount
	// Each Element will be an entry in splittedElements
	// No duplicate bit should exists and the split should be as fair as possible
	// Examples:
	// ElementType = Air|Earth|Water -> Split 2 -> Air|Earth, Water
	// ElementType = Air|Earth|Fire|Water -> Split 2 -> Air|Earth, Fire|Water
	// ElementType = Air|Water -> Split 3 -> Air, Water, None

	splittedElements.AddZeroed(splitCount);

	return splittedElements;
}

TArray<uint8> UElementalComponent::MergeElement(TArray<UElementalComponent*> elements)
{
	TArray<uint8> mergedElements;

	// Technical Test
	// Task #2.5

	// Take parameter elements and merge it into return parameters mergedElements
	// mergedElements should have for first entry the merge elements
	// mergedElements entry #1 to elements.Num() should be any duplicate element that could not have been moved into the merged entry (or None if there was no duplicate)
	// Examples:
	// elements = {Air|Earth, Fire|Water} -> mergedElements = {Air|Earth|Fire|Water, None, None}
	// elements = {Air, Fire|Water, Earth|Fire} -> mergedElements = {Air|Earth|Fire|Water, None, None, Fire}
	// elements = {Air, Air|Water, Water|Air} -> mergedElements = {Air|Water, None, Air, Water|Air}
	mergedElements.AddZeroed(elements.Num() + 1);
	
	return mergedElements;
}