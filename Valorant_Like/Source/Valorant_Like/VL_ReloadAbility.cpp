// Fill out your copyright notice in the Description page of Project Settings.


#include "VL_ReloadAbility.h"
#include "VL_FPSCharacter.h"

void UVL_ReloadAbility::Activate()
{
	UVL_AbilitySystemComponent* CharacterASC = Cast<UVL_AbilitySystemComponent>(GetOuter());
	if (!CharacterASC || !CharacterASC->GetCurrentAmmoCount() == MaxAmmoCount)	return;

	AVL_FPSCharacter* Character = Cast<AVL_FPSCharacter>(CharacterASC->GetOuter());

	// TODO : Play Reload animation
	
	if (ReloadAnimation != nullptr)
    {
    	UAnimInstance* AnimInstance = Character->GetMesh1P()->GetAnimInstance();
    	if (AnimInstance != nullptr)
    	{
    		FOnMontageEnded EndDelegate;
    		EndDelegate.BindUObject(this, &UVL_ReloadAbility::OnAnimationEnded);
    
    		AnimInstance->Montage_Play(ReloadAnimation);
    		AnimInstance->Montage_SetEndDelegate(EndDelegate, ReloadAnimation);
    	}
    }
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

void UVL_ReloadAbility::OnAnimationEnded(UAnimMontage* Montage, bool bInterrupted)
{
	UVL_AbilitySystemComponent* CharacterASC = Cast<UVL_AbilitySystemComponent>(GetOuter());

	if (CharacterASC)
		CharacterASC->SetCurrentAmmoCount(MaxAmmoCount);
}
