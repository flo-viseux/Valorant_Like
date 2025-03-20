// Fill out your copyright notice in the Description page of Project Settings.


#include "VL_HitAbility.h"

#include "VL_AbilitySystemComponent.h"

void UVL_HitAbility::Init()
{
	Super::Init();
}

void UVL_HitAbility::Activate(float Value)
{
	UVL_AbilitySystemComponent* CharacterASC = Cast<UVL_AbilitySystemComponent>(GetOuter());
	if (!CharacterASC) return;

	CharacterASC->SetCurrentHealth(CharacterASC->GetCurrentHealth() - Value);
}

bool UVL_HitAbility::CanActivate() const
{
	return Super::CanActivate();
}
