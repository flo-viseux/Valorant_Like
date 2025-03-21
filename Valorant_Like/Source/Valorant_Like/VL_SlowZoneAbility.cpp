// Fill out your copyright notice in the Description page of Project Settings.


#include "VL_SlowZoneAbility.h"

#include "VL_SlowZone.h"

void UVL_SlowZoneAbility::Activate(FVector Location)
{
	const FRotator SpawnRotation = FRotator(0, 0, 0);
	const FVector SpawnLocation = Location;
	
	//Set Spawn Collision Handling Override
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		
	AVL_SlowZone* SpawnedSlowZone = GetWorld()->SpawnActor<AVL_SlowZone>(SlowZoneClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
}
