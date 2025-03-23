// Fill out your copyright notice in the Description page of Project Settings.


#include "VL_AbilitySystemComponent.h"

#include "VL_FireAbility.h"
#include "VL_FPSCharacter.h"
#include "VL_ReloadAbility.h"
#include "GameFramework/CharacterMovementComponent.h"

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
	
	InitBaseSpeed(500.0f);
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

float UVL_AbilitySystemComponent::GetCurrentSpeed() const
{
	return  CurrentSpeed;
}

void UVL_AbilitySystemComponent::SetCurrentSpeed(float NewSpeed)
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

void UVL_AbilitySystemComponent::InitBaseSpeed(float InBaseSpeed)
{
    BaseSpeed = InBaseSpeed;
    CurrentSpeed = BaseSpeed;

    GetWorld()->GetTimerManager().SetTimer(
        SpeedModifierTimerHandle,
        this,
        &UVL_AbilitySystemComponent::CheckModifiersExpiration,
        0.1f, // Check every 0.1 secondes
        true
    );

	RecalculateSpeed();
}

void UVL_AbilitySystemComponent::AddSpeedModifier(FName SourceID, float Multiplier, float Duration)
{
    bool bExists = false;
    for (int32 i = 0; i < ActiveSpeedModifiers.Num(); i++)
    {
        if (ActiveSpeedModifiers[i].SourceID == SourceID)
        {
            ActiveSpeedModifiers[i].Multiplier = Multiplier;
            ActiveSpeedModifiers[i].Duration = Duration;
            ActiveSpeedModifiers[i].StartTime = GetWorld()->GetTimeSeconds();
            bExists = true;
            break;
        }
    }

    if (!bExists)
    {
        FSpeedModifier NewModifier(SourceID, Multiplier, Duration);
        NewModifier.StartTime = GetWorld()->GetTimeSeconds();
        ActiveSpeedModifiers.Add(NewModifier);
    }

    RecalculateSpeed();
}

void UVL_AbilitySystemComponent::RemoveSpeedModifier(FName SourceID)
{
    bool bRemoved = false;
    for (int32 i = ActiveSpeedModifiers.Num() - 1; i >= 0; i--)
    {
        if (ActiveSpeedModifiers[i].SourceID == SourceID)
        {
            ActiveSpeedModifiers.RemoveAt(i);
            bRemoved = true;
            break;
        }
    }

    if (bRemoved)
        RecalculateSpeed();
}

void UVL_AbilitySystemComponent::RecalculateSpeed()
{
    float FinalMultiplier = 1.0f;
    for (const FSpeedModifier& Modifier : ActiveSpeedModifiers)
    {
        FinalMultiplier *= Modifier.Multiplier;
    }
    
    CurrentSpeed = BaseSpeed * FinalMultiplier;
    
    AVL_FPSCharacter* OwnerCharacter = Cast<AVL_FPSCharacter>(GetOwner());
    if (OwnerCharacter)
    {
        OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = CurrentSpeed;
    }
}

void UVL_AbilitySystemComponent::CheckModifiersExpiration()
{
    float CurrentTime = GetWorld()->GetTimeSeconds();
    bool bNeedRecalculation = false;

    for (int32 i = ActiveSpeedModifiers.Num() - 1; i >= 0; i--)
    {
        if (ActiveSpeedModifiers[i].Duration > 0.0f &&
            (CurrentTime - ActiveSpeedModifiers[i].StartTime) >= ActiveSpeedModifiers[i].Duration)
        {
            ActiveSpeedModifiers.RemoveAt(i);
            bNeedRecalculation = true;
        }
    }

    if (bNeedRecalculation)
        RecalculateSpeed();
}

void UVL_AbilitySystemComponent::ClearAllSpeedModifiers()
{
    if (ActiveSpeedModifiers.Num() > 0)
    {
        ActiveSpeedModifiers.Empty();
        RecalculateSpeed();
    }
}
