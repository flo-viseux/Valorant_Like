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
			bIsReloading = true;

    		FOnMontageEnded EndDelegate;
    		EndDelegate.BindUObject(this, &UVL_ReloadAbility::OnAnimationEnded);

			float PlayRate = 1.0f;
			float BlendInTime = 0.25f;
			AnimInstance->Montage_Play(ReloadAnimation, PlayRate, EMontagePlayReturnType::MontageLength, 0.0f, true);
    		AnimInstance->Montage_SetEndDelegate(EndDelegate, ReloadAnimation);
    	}
    }
}

bool UVL_ReloadAbility::CanActivate() const
{
	UVL_AbilitySystemComponent* CharacterASC = Cast<UVL_AbilitySystemComponent>(GetOuter());
	if (!CharacterASC || !CharacterASC->GetCurrentAmmoCount() == MaxAmmoCount || bIsReloading)	return false;

	return true;
}

bool UVL_ReloadAbility::GetIsReloading() const
{
	return bIsReloading;
}

int UVL_ReloadAbility::GetMaxAmmoCount() const
{
	return MaxAmmoCount;
}

void UVL_ReloadAbility::OnAnimationEnded(UAnimMontage* Montage, bool bInterrupted)
{
	bIsReloading = false;
	UVL_AbilitySystemComponent* CharacterASC = Cast<UVL_AbilitySystemComponent>(GetOuter());

	if (CharacterASC)
		CharacterASC->SetCurrentAmmoCount(MaxAmmoCount);
}
