// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VL_AbilityBase.h"
#include "VL_SlowZoneAbility.generated.h"

/**
 * 
 */
UCLASS()
class VALORANT_LIKE_API UVL_SlowZoneAbility : public UVL_AbilityBase
{
	GENERATED_BODY()

public:
	virtual void Activate(FVector Location, UWorld* World) override;

	TSubclassOf<class AVL_SlowZone> SlowZoneClass;
};
