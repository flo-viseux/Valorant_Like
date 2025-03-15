// Copyright Epic Games, Inc. All Rights Reserved.

#include "Valorant_LikePickUpComponent.h"

UValorant_LikePickUpComponent::UValorant_LikePickUpComponent()
{
	// Setup the Sphere Collision
	SphereRadius = 32.f;
}

void UValorant_LikePickUpComponent::BeginPlay()
{
	Super::BeginPlay();

	// Register our Overlap Event
	OnComponentBeginOverlap.AddDynamic(this, &UValorant_LikePickUpComponent::OnSphereBeginOverlap);
}

void UValorant_LikePickUpComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Checking if it is a First Person Character overlapping
	AValorant_LikeCharacter* Character = Cast<AValorant_LikeCharacter>(OtherActor);
	if(Character != nullptr)
	{
		// Notify that the actor is being picked up
		OnPickUp.Broadcast(Character);

		// Unregister from the Overlap Event so it is no longer triggered
		OnComponentBeginOverlap.RemoveAll(this);
	}
}
