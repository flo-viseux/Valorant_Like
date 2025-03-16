// Fill out your copyright notice in the Description page of Project Settings.


#include "VL_FireAbility.h"
#include "VL_FPSCharacter.h"

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
			for (UVL_AbilityBase* Ability : CharacterASC->GetActiveAbilities())
			{
				Ability->ModifyProjectile(SpawnedProjectile);
			}

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
