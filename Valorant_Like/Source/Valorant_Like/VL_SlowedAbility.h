// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VL_AbilityBase.h"
#include "VL_SlowedAbility.generated.h"

/**
 * 
 */
UCLASS()
class VALORANT_LIKE_API UVL_SlowedAbility : public UVL_AbilityBase
{
	GENERATED_BODY()

	virtual void Init();
	virtual void Activate(float Value);
	virtual void Deactivate(float Value);
	virtual bool CanActivate() const;
};
