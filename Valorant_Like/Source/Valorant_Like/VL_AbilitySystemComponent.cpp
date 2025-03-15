// Fill out your copyright notice in the Description page of Project Settings.


#include "VL_AbilitySystemComponent.h"
#include "VL_FPSCharacter.h"

// Sets default values for this component's properties
UVL_AbilitySystemComponent::UVL_AbilitySystemComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UVL_AbilitySystemComponent::BeginPlay()
{
	Super::BeginPlay();

	AVL_FPSCharacter* OwnerCharacter = Cast<AVL_FPSCharacter>(GetOwner());
	if (!OwnerCharacter) return;

	ReloadAbility = NewObject<UVL_AbilityBase>(this, OwnerCharacter->ReloadAbility);
	FireAbility = NewObject<UVL_AbilityBase>(this, OwnerCharacter->FireAbility);
	CompetenceCAbility = NewObject<UVL_AbilityBase>(this, OwnerCharacter->CompetenceCAbility);
	CompetenceXAbility = NewObject<UVL_AbilityBase>(this, OwnerCharacter->CompetenceXAbility);
}

void UVL_AbilitySystemComponent::Fire()
{
	if (!ReloadAbility->CanActivate())
	return;
	
	ReloadAbility->Activate();
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

