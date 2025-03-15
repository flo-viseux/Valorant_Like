// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Valorant_LikeCharacter.h"
#include "VL_AbilitySystemComponent.h"
#include "GameFramework/Character.h"
#include "VL_FPSCharacter.generated.h"

UCLASS()
class VALORANT_LIKE_API AVL_FPSCharacter : public AValorant_LikeCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AVL_FPSCharacter();
	
	UPROPERTY(EditDefaultsOnly, Category="Abilities")
	TSubclassOf<UVL_AbilityBase> ReloadAbility;
	UPROPERTY(EditDefaultsOnly, Category="Abilities")
	TSubclassOf<UVL_AbilityBase> FireAbility;
	UPROPERTY(EditDefaultsOnly, Category="Abilities")
	TSubclassOf<UVL_AbilityBase> CompetenceXAbility;
	UPROPERTY(EditDefaultsOnly, Category="Abilities")
	TSubclassOf<UVL_AbilityBase> CompetenceCAbility;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* FireAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector MuzzleOffset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ReloadAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* CompetenceCAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* CompetenceXAction;

	UVL_AbilitySystemComponent* GetAbilitySystemComponent() const;

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Abilities")
	UVL_AbilitySystemComponent* AbilitySystemComponent;

	void StartFiring();
	void Reload();
	void UseCompetenceX();
	void UseCompentenceC();

};
