// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VL_AbilityBase.h"
#include "VL_FireAbility.generated.h"

/**
 * 
 */
UCLASS()
class VALORANT_LIKE_API UVL_FireAbility : public UVL_AbilityBase
{
	GENERATED_BODY()
public:
	virtual void Activate() override;

protected:
	UPROPERTY(EditDefaultsOnly, Category="Shooting")
	TSubclassOf<class AVL_Projectile> ProjectileClass;
};
