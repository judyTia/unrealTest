// Fill out your copyright notice in the Description page of Project Settings.

#include "TechnicalTest.h"
#include "PickableComponent.h"

#include "TTGameMode.h"
#include "TTCharacter.h"
#include "Camera/CameraComponent.h"

UPickableComponent::UPickableComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
}

void UPickableComponent::BeginPlay()
{
	Super::BeginPlay();

	if (!HasAnyFlags(EObjectFlags::RF_ClassDefaultObject))
	{
		ATTGameMode* gameMode = Utils::GetGameMode();
		if (gameMode != nullptr)
		{
			gameMode->PickableComponents.Add(this);
		}
	}
}

void UPickableComponent::EndPlay(EEndPlayReason::Type endPlayReason)
{
	if (!HasAnyFlags(EObjectFlags::RF_ClassDefaultObject))
	{
		ATTGameMode* gameMode = Utils::GetGameMode();
		if (gameMode != nullptr)
		{
			gameMode->PickableComponents.Remove(this);
		}
	}

	Super::EndPlay(endPlayReason);
}

void UPickableComponent::TickComponent(float deltaTime, enum ELevelTick tickType, FActorComponentTickFunction *thisTickFunction)
{
	if (PickedUpBy)
	{
		USceneComponent* sceneComp = GetAttachParent();
		if (sceneComp == nullptr)
		{
			sceneComp = this;
		}
		
		FTransform desiredTransform = RelativePickedUpTransform * PickedUpBy->FirstPersonCameraComponent->GetComponentTransform();

		FVector deltaLocation = desiredTransform.GetTranslation() - GetComponentLocation();

		FVector deltaDir;
		float deltaLength;
		deltaLocation.ToDirectionAndLength(deltaDir, deltaLength);

		FTransform moveTransform = desiredTransform;
		float approachLength = Utils::Approach(0.0f, deltaLength, PickedUpApproachFactor, deltaTime);
		moveTransform.SetTranslation(desiredTransform.GetTranslation() - deltaDir * (deltaLength - approachLength));

		FHitResult hit;
		sceneComp->SetWorldTransform(moveTransform, true, &hit);

		if (hit.bBlockingHit)
		{
			FVector impactToDesired = desiredTransform.GetTranslation() - hit.Location;

			if (impactToDesired.SizeSquared() > FMath::Square(OffsetForDrop))
			{
				PickedUpBy->ForceDropPickable();
			}
		}
	}
}

void UPickableComponent::DisablePhysics()
{
	UPrimitiveComponent* parent = Cast<UPrimitiveComponent>(GetAttachParent());
	if (parent != nullptr)
	{
		parent->SetSimulatePhysics(false);
	}
}

void UPickableComponent::EnablePhysics()
{
	UPrimitiveComponent* parent = Cast<UPrimitiveComponent>(GetAttachParent());
	if (parent != nullptr)
	{
		parent->SetSimulatePhysics(true);
	}
}

void UPickableComponent::OnPickup_Implementation(ATTCharacter* pawn)
{
	if (pawn != nullptr)
	{
		//Utils::PrintToScreen("Picked up");

		PickedUpBy = pawn;
		RelativePickedUpTransform = GetComponentTransform() * PickedUpBy->FirstPersonCameraComponent->GetComponentTransform().Inverse();

		DisablePhysics();
	}
}

void UPickableComponent::OnDrop_Implementation(class ATTCharacter* pawn)
{
	//Utils::PrintToScreen("Dropped down");
	PickedUpBy = nullptr;

	EnablePhysics();
}
