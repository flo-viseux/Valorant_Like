// Fill out your copyright notice in the Description page of Project Settings.


#include "VL_AbilitySystemComponent.h"

#include "VL_FireAbility.h"
#include "VL_FPSCharacter.h"
#include "VL_ReloadAbility.h"

// Sets default values for this component's properties
UVL_AbilitySystemComponent::UVL_AbilitySystemComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UVL_AbilitySystemComponent::BeginPlay()
{
	Super::BeginPlay();

	ReloadAbility = NewObject<UVL_ReloadAbility>(this, ReloadAbilityClass);
	FireAbility = NewObject<UVL_FireAbility>(this, FireAbilityClass);
	CompetenceCAbility = NewObject<UVL_AbilityBase>(this, CompetenceCAbilityClass);
	CompetenceXAbility = NewObject<UVL_AbilityBase>(this, CompetenceXAbilityClass);
	Cast<UVL_FireAbility>(FireAbility)->ProjectileClass = ProjectileClass;

	CurrentAmmoCount = ReloadAbility->GetMaxAmmoCount();
}

void UVL_AbilitySystemComponent::Fire()
{
	if (!FireAbility->CanActivate())
	return;
	
	FireAbility->Activate();
	CurrentAmmoCount--;
}

void UVL_AbilitySystemComponent::Reload()
{
	if (!ReloadAbility->CanActivate())
		return;
	
	ReloadAbility->Activate();
}

void UVL_AbilitySystemComponent::UseCompetenceX()
{
	if (!CompetenceXAbility->CanActivate())
		return;

	CompetenceXAbility->Activate();
}

void UVL_AbilitySystemComponent::UseCompetenceC()
{
	if (!CompetenceCAbility->CanActivate())
		return;

	CompetenceCAbility->Activate();
}

void UVL_AbilitySystemComponent::ActivateAbility(FName AbilityName)
{
	for (UVL_AbilityBase* Ability : ActiveAbilities)
	{
		if (Ability && Ability->GetFName() == AbilityName)
		{
			Ability->Activate();
			break;
		}
	}
}

int UVL_AbilitySystemComponent::GetCurrentAmmoCount() const
{
	return CurrentAmmoCount;
}

void UVL_AbilitySystemComponent::SetCurrentAmmoCount(int NewAmmoCount)
{
	CurrentAmmoCount = NewAmmoCount;
}

