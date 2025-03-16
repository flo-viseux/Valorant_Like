// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VL_AbilityBase.h"
#include "VL_ReloadAbility.generated.h"

/**
 * 
 */
UCLASS()
class VALORANT_LIKE_API UVL_ReloadAbility : public UVL_AbilityBase
{
	GENERATED_BODY()
public:
	virtual void Activate() override;

	virtual bool CanActivate() const override;

	int GetMaxAmmoCount() const;

protected:
	UPROPERTY(EditDefaultsOnly, Category="Attributes")
	int MaxAmmoCount = 30;
};
