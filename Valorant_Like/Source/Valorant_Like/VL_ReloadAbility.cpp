// Fill out your copyright notice in the Description page of Project Settings.


#include "VL_ReloadAbility.h"
#include "VL_FPSCharacter.h"

void UVL_ReloadAbility::Activate()
{
	UVL_AbilitySystemComponent* CharacterASC = Cast<UVL_AbilitySystemComponent>(GetOuter());
	if (!CharacterASC || !CharacterASC->GetCurrentAmmoCount() == MaxAmmoCount)	return;

	// TODO : Play Reload animation
	CharacterASC->SetCurrentAmmoCount(MaxAmmoCount);
}

bool UVL_ReloadAbility::CanActivate() const
{
	UVL_AbilitySystemComponent* CharacterASC = Cast<UVL_AbilitySystemComponent>(GetOuter());
	if (!CharacterASC || !CharacterASC->GetCurrentAmmoCount() == MaxAmmoCount)	return false;

	return true;
}

int UVL_ReloadAbility::GetMaxAmmoCount() const
{
	return MaxAmmoCount;
}
