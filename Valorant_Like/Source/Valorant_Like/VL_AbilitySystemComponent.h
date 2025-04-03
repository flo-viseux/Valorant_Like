// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VL_AbilityBase.h"
#include "VL_FireAbility.h"
#include "VL_ReloadAbility.h"
#include "VL_HitAbility.h"
#include "Components/ActorComponent.h"
#include "VL_AbilitySystemComponent.generated.h"

USTRUCT(BlueprintType)
struct FSpeedModifier
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName SourceID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Multiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Duration;

	UPROPERTY()
	float StartTime;

	FSpeedModifier()
		: SourceID(NAME_None)
		, Multiplier(1.0f)
		, Duration(-1.0f)
		, StartTime(0.0f)
	{
	}

	FSpeedModifier(FName InSourceID, float InMultiplier, float InDuration = -1.0f)
		: SourceID(InSourceID)
		, Multiplier(InMultiplier)
		, Duration(InDuration)
		, StartTime(0.0f)
	{
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAmmoChanged, int32, CurrentAmmo, int32, MaxAmmo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAbilityCooldownChanged, FName, AbilityName, float, RemainingCooldown);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAbilityActiveStateChanged, FName, AbilityName, bool, bIsActive);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAbilityIconInit, FName, AbilityName, UTexture2D*, AbilityIcon);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VALORANT_LIKE_API UVL_AbilitySystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UVL_AbilitySystemComponent();

	virtual void BeginPlay() override;

	// Delegates
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnAmmoChanged OnAmmoChanged;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnAbilityCooldownChanged OnAbilityCooldownChanged;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnAbilityActiveStateChanged OnAbilityActiveStateChanged;
	
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnAbilityIconInit OnAbilityIconInit;

	UFUNCTION(BlueprintCallable)
	void InitIcons();
	
	void Fire();
	void Reload();
	void UseCompetenceX();
	void UseCompetenceC();
	void Hit(float Damage);

	void ActivateAbility(FName AbilityName);
	TArray<UVL_AbilityBase*> GetActiveAbilities() const { return ActiveAbilities; }
	
	void AddActiveAbility(UVL_AbilityBase* NewAbility);

	void RemoveActiveAbility(UVL_AbilityBase* Ability);

	
	UPROPERTY(EditDefaultsOnly, Category="Abilities")
	TSubclassOf<UVL_ReloadAbility> ReloadAbilityClass;
	UPROPERTY(EditDefaultsOnly, Category="Abilities")
	TSubclassOf<UVL_FireAbility> FireAbilityClass;
	UPROPERTY(EditDefaultsOnly, Category="Abilities")
	TSubclassOf<UVL_AbilityBase> CompetenceXAbilityClass;
	UPROPERTY(EditDefaultsOnly, Category="Abilities")
	TSubclassOf<UVL_AbilityBase> CompetenceCAbilityClass;
	UPROPERTY(EditDefaultsOnly, Category="Abilities")
	TSubclassOf<UVL_HitAbility> HitAbilityClass;

	
	
	UPROPERTY(VisibleAnywhere, Category="Attributes")
	UVL_ReloadAbility* ReloadAbility;
	
	UPROPERTY(VisibleAnywhere, Category="Attributes")
	UVL_FireAbility* FireAbility;
	
	UPROPERTY(VisibleAnywhere, Category="Attributes")
	UVL_AbilityBase* CompetenceXAbility;
	
	UPROPERTY(VisibleAnywhere, Category="Attributes")
	UVL_AbilityBase* CompetenceCAbility;
	
	UPROPERTY(VisibleAnywhere, Category="Abilities")
	UVL_HitAbility* HitAbility;
	
	int GetCurrentAmmoCount() const;

	void SetCurrentAmmoCount(int NewAmmoCount);

	int GetCurrentHealth() const;

	void SetCurrentHealth(int NewAmmoCount);

	float GetCurrentSpeed() const;

	void SetCurrentSpeed(float NewSpeed);

	UFUNCTION(BlueprintCallable, Category = "Character|Movement")
	void InitBaseSpeed(float InBaseSpeed);

	UFUNCTION(BlueprintCallable, Category = "Character|Movement")
	void AddSpeedModifier(FName SourceID, float Multiplier, float Duration = -1.0f);

	UFUNCTION(BlueprintCallable, Category = "Character|Movement")
	void RemoveSpeedModifier(FName SourceID);

	UFUNCTION(BlueprintCallable, Category = "Character|Movement")
	void RecalculateSpeed();

	UFUNCTION()
	void CheckModifiersExpiration();

	UFUNCTION(BlueprintCallable, Category = "Character|Movement")
	void ClearAllSpeedModifiers();

protected:
	UPROPERTY(EditDefaultsOnly, Category="Attributes")
	float InitialHealth;
	
	UPROPERTY(EditDefaultsOnly, Category="Attributes")
	float BaseSpeed;
	
private:
	UPROPERTY()
	TArray<UVL_AbilityBase*> ActiveAbilities;
	
	UPROPERTY()
	TArray<FSpeedModifier> ActiveSpeedModifiers;

	UPROPERTY()
	float CurrentSpeed;

	FTimerHandle SpeedModifierTimerHandle;

	int CurrentAmmoCount = 0;	
	int MaxAmmoCount = 0;

	float CurrentHealth = 0;
};
