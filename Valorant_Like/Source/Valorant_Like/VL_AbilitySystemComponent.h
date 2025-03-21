// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VL_AbilityBase.h"
#include "VL_FireAbility.h"
#include "VL_ReloadAbility.h"
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
	void Slowed(float Slow);
	void Hit(float Damage);

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
	TSubclassOf<class AVL_Projectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category="Attributes")
	float InitialHealth;
	
	UPROPERTY(EditDefaultsOnly, Category="Attributes")
	float BaseSpeed;
	
private:
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
	
	UPROPERTY()
	TArray<FSpeedModifier> ActiveSpeedModifiers;

	UPROPERTY()
	float CurrentSpeed;

	FTimerHandle SpeedModifierTimerHandle;

	int CurrentAmmoCount = 0;

	float CurrentHealth = 0;
};
