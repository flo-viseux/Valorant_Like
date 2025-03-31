// Fill out your copyright notice in the Description page of Project Settings.


#include "VL_AbilityBase.h"

#include "VL_AbilitySystemComponent.h"

void UVL_AbilityBase::Init()
{
	bIsBulletModifier = false;
	bIsOnCooldown = false;
	CooldownDuration = 0.0f;
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
    return !bIsOnCooldown;
}

void UVL_AbilityBase::StartCooldown()
{
	if (CooldownDuration <= 0.0f)
		return;
        
	bIsOnCooldown = true;
    
	UWorld* World = GetWorld();
	if (World)
	{
		World->GetTimerManager().SetTimer(
			CooldownTimerHandle,
			this,
			&UVL_AbilityBase::EndCooldown,
			CooldownDuration,
			false
		);

		World->GetTimerManager().SetTimer(
			CooldownUpdateTimerHandle,
			FTimerDelegate::CreateUObject(this, &UVL_AbilityBase::UpdateCooldownUI),
			0.1f, // Update every 0.1 secondes
			true
		);
	}
}

void UVL_AbilityBase::EndCooldown()
{bIsOnCooldown = false;
    
	UVL_AbilitySystemComponent* AbilitySystem = Cast<UVL_AbilitySystemComponent>(GetOuter());
	if (AbilitySystem)
	{
		AbilitySystem->OnAbilityCooldownChanged.Broadcast(GetFName(), 0.0f);
	}
}

void UVL_AbilityBase::UpdateCooldownUI()
{
	UVL_AbilitySystemComponent* AbilitySystem = Cast<UVL_AbilitySystemComponent>(GetOuter());
	if (AbilitySystem)
	{
		float RemainingTime = GetRemainingCooldown();
		AbilitySystem->OnAbilityCooldownChanged.Broadcast(GetFName(), RemainingTime);
        
		// Stop update UI, cooldown is finished
		if (RemainingTime <= 0.0f)
		{
			UWorld* World = GetWorld();
			if (World)
			{
				World->GetTimerManager().ClearTimer(CooldownUpdateTimerHandle);
			}
		}
	}
}

float UVL_AbilityBase::GetRemainingCooldown() const
{
	if (!bIsOnCooldown)
		return 0.0f;
        
	UWorld* World = GetWorld();
	if (World)
	{
		float ElapsedTime = World->GetTimerManager().GetTimerElapsed(CooldownTimerHandle);
		float TotalTime = World->GetTimerManager().GetTimerRate(CooldownTimerHandle);
		return FMath::Max(0.0f, TotalTime - ElapsedTime);
	}
    
	return 0.0f;
}

bool UVL_AbilityBase::IsOnCooldown() const
{
	return bIsOnCooldown;
}
