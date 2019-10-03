// Fill out your copyright notice in the Description page of Project Settings.

#include "TechnicalTest.h"
#include "PickableMagnetComponent.h"

#include "PickableComponent.h"

UPickableMagnetComponent::UPickableMagnetComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
}

void UPickableMagnetComponent::TickComponent(float deltaTime, enum ELevelTick tickType, FActorComponentTickFunction *thisTickFunction)
{
	TArray<UPrimitiveComponent*> overlappingComponents;
	GetOverlappingComponents(overlappingComponents);

	if (CurrentPickable != nullptr)
	{
		if (CurrentPickable->PickedUpBy != nullptr)
		{
			OnPickupEvent.Broadcast(CurrentPickable);
			DetachPickable(CurrentPickable);
		}
		else
		{
			CurrentPickable->DisablePhysics();

			USceneComponent* sceneComp = CurrentPickable->GetAttachParent();
			if (sceneComp == nullptr)
			{
				sceneComp = CurrentPickable;
			}

			TWEAKABLE float Approach = 0.9999f;
			sceneComp->SetWorldLocation(Utils::Approach(sceneComp->GetComponentLocation(), GetComponentLocation(), Approach, deltaTime));
		}
	}

	if (!bActive)
	{
		return;
	}

	if (CurrentPickable == nullptr)
	{
		for (UPrimitiveComponent* comp : overlappingComponents)
		{
			UPickableComponent* pickable = Cast<UPickableComponent>(comp->GetOwner()->GetComponentByClass(UPickableComponent::StaticClass()));
			if (pickable != nullptr && pickable->PickedUpBy == nullptr)
			{
				USceneComponent* sceneComp = pickable->GetAttachParent();
				if (sceneComp == nullptr)
				{
					sceneComp = pickable;
				}

				AttachPickable(pickable);
				OnDropEvent.Broadcast(CurrentPickable);
			}
		}
	}
}

bool UPickableMagnetComponent::IsAvailable() const
{
	TArray<UPrimitiveComponent*> overlappingComponents;
	GetOverlappingComponents(overlappingComponents);

	return overlappingComponents.Num() == 0;
}

void UPickableMagnetComponent::AttachPickable(UPickableComponent* pickable)
{
	CurrentPickable = pickable;
}

void UPickableMagnetComponent::DetachPickable(UPickableComponent* pickable)
{
	CurrentPickable = nullptr;
}