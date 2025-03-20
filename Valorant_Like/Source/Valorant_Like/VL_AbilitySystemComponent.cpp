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
	ReloadAbility->Init();
	FireAbility = NewObject<UVL_FireAbility>(this, FireAbilityClass);
	FireAbility->Init();
	CompetenceCAbility = NewObject<UVL_AbilityBase>(this, CompetenceCAbilityClass);
	CompetenceCAbility->Init();
	CompetenceXAbility = NewObject<UVL_AbilityBase>(this, CompetenceXAbilityClass);
	CompetenceXAbility->Init();
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

void UVL_AbilitySystemComponent::Slowed(float Slow)
{
	CurrentSpeed -= Slow;
}

void UVL_AbilitySystemComponent::Hit(float Damage)
{
	CurrentHealth -= Damage;
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

void UVL_AbilitySystemComponent::AddActiveAbility(UVL_AbilityBase* NewAbility)
{
	if (ActiveAbilities.Contains(NewAbility))
		return;
	
	ActiveAbilities.Add(NewAbility);
}

void UVL_AbilitySystemComponent::RemoveActiveAbility(UVL_AbilityBase* Ability)
{
	if (!ActiveAbilities.Contains(Ability))
		return;
	
	ActiveAbilities.Remove(Ability);
}


int UVL_AbilitySystemComponent::GetCurrentAmmoCount() const
{
	return CurrentAmmoCount;
}

void UVL_AbilitySystemComponent::SetCurrentAmmoCount(int NewAmmoCount)
{
	CurrentAmmoCount = NewAmmoCount;
}

int UVL_AbilitySystemComponent::GetCurrentSpeed() const
{
	return  CurrentSpeed;
}

void UVL_AbilitySystemComponent::SetCurrentSpeed(int NewSpeed)
{
	CurrentSpeed = NewSpeed;
}

int UVL_AbilitySystemComponent::GetCurrentHealth() const
{
	return  CurrentHealth;
}

void UVL_AbilitySystemComponent::SetCurrentHealth(int NewAmmoCount)
{
}
