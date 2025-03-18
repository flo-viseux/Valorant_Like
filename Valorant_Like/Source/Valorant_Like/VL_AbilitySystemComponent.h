// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VL_AbilityBase.h"
#include "VL_FireAbility.h"
#include "VL_ReloadAbility.h"
#include "Components/ActorComponent.h"
#include "VL_AbilitySystemComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VALORANT_LIKE_API UVL_AbilitySystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UVL_AbilitySystemComponent();

	virtual void BeginPlay() override;

	void Fire();
	void Reload();
	void UseCompetenceX();
	void UseCompetenceC();

	void ActivateAbility(FName AbilityName);
	TArray<UVL_AbilityBase*> GetActiveAbilities() const { return ActiveAbilities; }
	
	void AddActiveAbility(UVL_AbilityBase* NewAbility);

	void RemoveActiveAbility(UVL_AbilityBase* Ability);

	
	UPROPERTY(EditDefaultsOnly, Category="Abilities")
	TSubclassOf<UVL_AbilityBase> ReloadAbilityClass;
	UPROPERTY(EditDefaultsOnly, Category="Abilities")
	TSubclassOf<UVL_AbilityBase> FireAbilityClass;
	UPROPERTY(EditDefaultsOnly, Category="Abilities")
	TSubclassOf<UVL_AbilityBase> CompetenceXAbilityClass;
	UPROPERTY(EditDefaultsOnly, Category="Abilities")
	TSubclassOf<UVL_AbilityBase> CompetenceCAbilityClass;
	
	int GetCurrentAmmoCount() const;

	void SetCurrentAmmoCount(int NewAmmoCount);

protected:
	UPROPERTY()
	TArray<UVL_AbilityBase*> ActiveAbilities;
	
	UPROPERTY(VisibleAnywhere, Category="Attributes")
	UVL_ReloadAbility* ReloadAbility;
	
	UPROPERTY(VisibleAnywhere, Category="Attributes")
	UVL_FireAbility* FireAbility;
	
	UPROPERTY(VisibleAnywhere, Category="Attributes")
	UVL_AbilityBase* CompetenceXAbility;
	
	UPROPERTY(VisibleAnywhere, Category="Attributes")
	UVL_AbilityBase* CompetenceCAbility;
	
	UPROPERTY(EditDefaultsOnly, Category="Attributes")
	TSubclassOf<class AVL_Projectile> ProjectileClass;

	int CurrentAmmoCount = 0;
};
