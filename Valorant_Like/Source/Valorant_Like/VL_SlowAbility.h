// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VL_AbilityBase.h"
#include "VL_SlowAbility.generated.h"

/**
 * 
 */
UCLASS()
class VALORANT_LIKE_API UVL_SlowAbility : public UVL_AbilityBase
{
	GENERATED_BODY()
	
public:
	virtual void ModifyProjectile(AVL_Projectile* Projectile) override;

	virtual bool CanActivate() const override;

	virtual void Activate() override;

	virtual void Init() override;

protected:

	bool bAlreadyUsed = false;
};
