// Fill out your copyright notice in the Description page of Project Settings.


#include "VL_SlowedAbility.h"

#include "VL_AbilitySystemComponent.h"

void UVL_SlowedAbility::Init()
{
	Super::Init();
}

void UVL_SlowedAbility::Activate(float Value)
{
	UVL_AbilitySystemComponent* CharacterASC = Cast<UVL_AbilitySystemComponent>(GetOuter());
	if (!CharacterASC) return;

	CharacterASC->SetCurrentSpeed(CharacterASC->GetCurrentSpeed() - Value);
}

void UVL_SlowedAbility::Deactivate(float Value)
{
	UVL_AbilitySystemComponent* CharacterASC = Cast<UVL_AbilitySystemComponent>(GetOuter());
	if (!CharacterASC) return;

	CharacterASC->SetCurrentSpeed(CharacterASC->GetCurrentSpeed() + Value);
}

bool UVL_SlowedAbility::CanActivate() const
{
	return Super::CanActivate();
}