// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VL_Projectile.h"
#include "VL_AbilityBase.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class VALORANT_LIKE_API UVL_AbilityBase : public UObject
{
	GENERATED_BODY()
	
public:
	bool bIsBulletModifier;
	bool bIsOnCooldown;
	
	UPROPERTY(EditDefaultsOnly, Category="Attributes")
	float CooldownDuration;

	FTimerHandle CooldownTimerHandle;
	FTimerHandle CooldownUpdateTimerHandle;

	virtual void Init();
	virtual void Init(FName InCompetenceName);
	virtual void Activate();
	virtual void Deactivate();
	virtual void Activate(FVector Location, UWorld* World);
	virtual void Activate(float Value);
	virtual void Deactivate(float Value);
	virtual void ModifyProjectile(AVL_Projectile* Projectile);
	virtual bool CanActivate() const;

	void StartCooldown();
	void EndCooldown();
	void UpdateCooldownUI();
	float GetRemainingCooldown() const;
	bool IsOnCooldown() const;
	FName CompetenceName;
};
