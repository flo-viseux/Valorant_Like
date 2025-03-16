// Fill out your copyright notice in the Description page of Project Settings.


#include "VL_FPSCharacter.h"

#include "EnhancedInputComponent.h"
#include "VL_ReloadAbility.h"

// Sets default values
AVL_FPSCharacter::AVL_FPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MuzzleOffset = FVector(100.0f, 0.0f, 10.0f);

	AbilitySystemComponent = CreateDefaultSubobject<UVL_AbilitySystemComponent>(TEXT("AbilitySystemComp"));
}

UVL_AbilitySystemComponent* AVL_FPSCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

// Called when the game starts or when spawned
void AVL_FPSCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called to bind functionality to input
void AVL_FPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &AVL_FPSCharacter::StartFiring);
		EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Started, this, &AVL_FPSCharacter::Reload);
		EnhancedInputComponent->BindAction(CompetenceXAction, ETriggerEvent::Started, this, &AVL_FPSCharacter::UseCompetenceX);
		EnhancedInputComponent->BindAction(CompetenceCAction, ETriggerEvent::Started, this, &AVL_FPSCharacter::UseCompentenceC);
	}
}

void AVL_FPSCharacter::StartFiring()
{
	AbilitySystemComponent->Fire();
}

void AVL_FPSCharacter::Reload()
{
	AbilitySystemComponent->Reload();
}

void AVL_FPSCharacter::UseCompetenceX()
{
	AbilitySystemComponent->UseCompetenceX();
}

void AVL_FPSCharacter::UseCompentenceC()
{
	AbilitySystemComponent->UseCompetenceC();
}

