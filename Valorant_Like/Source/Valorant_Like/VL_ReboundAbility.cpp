// Fill out your copyright notice in the Description page of Project Settings.


#include "VL_ReboundAbility.h"

#include "VL_AbilitySystemComponent.h"

void UVL_ReboundAbility::ModifyProjectile(AVL_Projectile* Projectile)
{
	if (!IsValid(Projectile))
		return;

	Projectile->GetProjectileMovement()->bShouldBounce = true;
	Projectile->InitialLifeSpan = 2.0f;
	Projectile->GetProjectileMovement()->Bounciness = .5f;
	Projectile->GetProjectileMovement()->Friction = 0.0f;
	Projectile->SetMaxBoundCount(ReboundCount);

	Deactivate();
    	StartCooldown();
}

bool UVL_ReboundAbility::CanActivate() const
{
	return Super::CanActivate();
}

void UVL_ReboundAbility::Deactivate()
{
	UVL_AbilitySystemComponent* CharacterASC = Cast<UVL_AbilitySystemComponent>(GetOuter());
	if (!CharacterASC) return;

	CharacterASC->RemoveActiveAbility(this);
    	bIsActive = false;
    	CharacterASC->OnAbilityActiveStateChanged.Broadcast(CompetenceName, false);
}

void UVL_ReboundAbility::Activate()
{
	if (bIsActive)
	{
		Deactivate();
		return;
	}
	
	if (bIsOnCooldown)
		return;
	
	UVL_AbilitySystemComponent* CharacterASC = Cast<UVL_AbilitySystemComponent>(GetOuter());
	if (!CharacterASC) return;

	CharacterASC->AddActiveAbility(this);
    	bIsActive = true;
    	CharacterASC->OnAbilityActiveStateChanged.Broadcast(CompetenceName, true);

}

void UVL_ReboundAbility::Init(FName InCompetenceName)
{	
	Super::Init(InCompetenceName);
	bIsOnCooldown = false;
	bIsBulletModifier = true;
	bIsActive = false;
}
