// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VL_AbilityBase.h"
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

protected:
	UPROPERTY()
	TArray<UVL_AbilityBase*> ActiveAbilities;

	UVL_AbilityBase* ReloadAbility;
	UVL_AbilityBase* FireAbility;
	UVL_AbilityBase* CompetenceXAbility;
	UVL_AbilityBase* CompetenceCAbility;
		
};
