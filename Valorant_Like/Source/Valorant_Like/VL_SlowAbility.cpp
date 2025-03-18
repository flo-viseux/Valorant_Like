// Fill out your copyright notice in the Description page of Project Settings.


#include "VL_SlowAbility.h"

#include "VL_AbilitySystemComponent.h"

void UVL_SlowAbility::ModifyProjectile(AVL_Projectile* Projectile)
{
	if (!IsValid(Projectile))
		return;

	Projectile->InitialLifeSpan = 2.0f;
	Projectile->GetProjectileMovement()->bShouldBounce = true;
	Projectile->GetProjectileMovement()->InitialSpeed = 3000.f;
	Projectile->GetProjectileMovement()->MaxSpeed = 3000.f;
	Projectile->GetProjectileMovement()->ProjectileGravityScale = 3.0f;
	Projectile->bIsSlowProjectile = true;
}

bool UVL_SlowAbility::CanActivate() const
{
	return Super::CanActivate();
}

void UVL_SlowAbility::Activate()
{
	UVL_AbilitySystemComponent* CharacterASC = Cast<UVL_AbilitySystemComponent>(GetOuter());
	if (!CharacterASC) return;

	CharacterASC->AddActiveAbility(this);
}

void UVL_SlowAbility::Init()
{
	bIsBulletModifier = true;
}