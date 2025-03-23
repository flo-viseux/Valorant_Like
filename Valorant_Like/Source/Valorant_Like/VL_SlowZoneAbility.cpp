// Fill out your copyright notice in the Description page of Project Settings.


#include "VL_SlowZoneAbility.h"

#include "VL_SlowZone.h"

void UVL_SlowZoneAbility::Activate(FVector Location, UWorld* World)
{
	if (World && SlowZoneClass)
	{
		const FRotator SpawnRotation = FRotator(0, 0, 0);
		const FVector SpawnLocation = Location;
        
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
            
		AVL_SlowZone* SpawnedSlowZone = World->SpawnActor<AVL_SlowZone>(SlowZoneClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
	}
}
