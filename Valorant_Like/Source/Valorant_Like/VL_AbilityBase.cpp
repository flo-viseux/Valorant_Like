// Fill out your copyright notice in the Description page of Project Settings.


#include "VL_AbilityBase.h"

void UVL_AbilityBase::Init()
{
	bIsBulletModifier = false;
}

void UVL_AbilityBase::Activate()
{
}

void UVL_AbilityBase::Deactivate()
{
}

void UVL_AbilityBase::Activate(FVector Location, UWorld* World)
{
}

void UVL_AbilityBase::Activate(float Value)
{
}

void UVL_AbilityBase::Deactivate(float Value)
{
}

void UVL_AbilityBase::ModifyProjectile(AVL_Projectile* Projectile)
{
}

bool UVL_AbilityBase::CanActivate() const
{
	return true;
}
