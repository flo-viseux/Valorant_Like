// Fill out your copyright notice in the Description page of Project Settings.


#include "VL_FireAbility.h"
#include "VL_FPSCharacter.h"
#include "VL_SlowAbility.h"
#include "Kismet/GameplayStatics.h"

void UVL_FireAbility::Activate()
{
	UVL_AbilitySystemComponent* CharacterASC = Cast<UVL_AbilitySystemComponent>(GetOuter());
	if (!CharacterASC) return;
	
	AVL_FPSCharacter* Character = Cast<AVL_FPSCharacter>(CharacterASC->GetOuter());
	
	if (!Character || !ProjectileClass) return;

	UWorld* const World = GetWorld();
	if (World != nullptr)
	{
		APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
		const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
		const FVector SpawnLocation = Character->GetActorLocation() + SpawnRotation.RotateVector(Character->MuzzleOffset);
	
		//Set Spawn Collision Handling Override
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
		
		AVL_Projectile* SpawnedProjectile = Character->GetWorld()->SpawnActor<AVL_Projectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);

		if (SpawnedProjectile)
		{
			if (FireAnimation != nullptr)
			{
				UAnimInstance* AnimInstance = Character->GetMesh1P()->GetAnimInstance();
				if (AnimInstance != nullptr)
				{
					AnimInstance->Montage_Play(FireAnimation);
				}
			}

			UVL_SlowAbility* SlowAbility = nullptr;
			
			for (UVL_AbilityBase* Ability : CharacterASC->GetActiveAbilities())
			{
				if (Ability->bIsBulletModifier)
					Ability->ModifyProjectile(SpawnedProjectile);

				UVL_SlowAbility* slow = Cast<UVL_SlowAbility>(Ability);
				if (slow)
					SlowAbility = slow;

				CharacterASC->RemoveActiveAbility(Ability);
			}
			
			if (SlowAbility && SlowAbility->SlowOrbeSound != nullptr)
				UGameplayStatics::PlaySoundAtLocation(this, SlowAbility->SlowOrbeSound, Character->GetActorLocation());
			else if (FireSound != nullptr)
    			UGameplayStatics::PlaySoundAtLocation(this, FireSound, Character->GetActorLocation());

			SpawnedProjectile->SetDamage(Damage);
		}
	}
}

bool UVL_FireAbility::CanActivate() const
{
	UVL_AbilitySystemComponent* CharacterASC = Cast<UVL_AbilitySystemComponent>(GetOuter());
	if (!CharacterASC || CharacterASC->GetCurrentAmmoCount() == 0) return false;
	
	return true;
}
