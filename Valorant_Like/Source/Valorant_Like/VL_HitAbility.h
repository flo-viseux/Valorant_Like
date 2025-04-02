// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VL_AbilityBase.h"
#include "VL_HitAbility.generated.h"

/**
 * 
 */
UCLASS()
class VALORANT_LIKE_API UVL_HitAbility : public UVL_AbilityBase
{
	GENERATED_BODY()

public:
	virtual void Init() override;
	virtual void Activate(float Value) override;
	virtual bool CanActivate() const override;
};
