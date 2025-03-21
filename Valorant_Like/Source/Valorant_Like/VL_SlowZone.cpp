// Fill out your copyright notice in the Description page of Project Settings.

#include "VL_SlowZone.h"

#include "VL_FPSCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/MaterialInterface.h"

// Sets default values
AVL_SlowZone::AVL_SlowZone()
{
 	// Set this actor to call Tick() every frame.
	PrimaryActorTick.bCanEverTick = true;

	// Create the static mesh component (cylinder)
	CylinderMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CylinderMesh"));
	RootComponent = CylinderMesh;
	
	// Load a cylinder static mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CylinderAsset(TEXT("/Engine/BasicShapes/Cylinder"));
	if (CylinderAsset.Succeeded())
	{
		CylinderMesh->SetStaticMesh(CylinderAsset.Object);
	}

	// Adjust the cylinder to be flat
	CylinderMesh->SetRelativeScale3D(FVector(1.0f, 1.0f, 0.1f));
	
	// Create the collision component
	CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetupAttachment(RootComponent);
	CollisionComponent->SetCapsuleHalfHeight(10.0f);
	CollisionComponent->SetCapsuleRadius(100.0f);
	CollisionComponent->SetCollisionProfileName(TEXT("Trigger"));

	// Add particle effect component (optional)
	EffectComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EffectComponent"));
	EffectComponent->SetupAttachment(RootComponent);
	
	// Default properties
	SlowAmount = 0.5f; // 50% slow
	ZoneDuration = 5.0f; // 5 seconds before shrinking
	GrowDuration = 1.0f; // 1 second to grow
	ShrinkDuration = 1.0f; // 1 second to shrink
	MaxScale = 5.0f; // Maximum scale
	
	// Set initial state
	CurrentState = EZoneState::Growing;
	ElapsedTime = 0.0f;
}

// Called when the game starts or when spawned
void AVL_SlowZone::BeginPlay()
{
	Super::BeginPlay();
	
	// Set initial scale to 0
	SetActorScale3D(FVector(0.0f, 0.0f, 0.0f));
	
	// Bind overlap events
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AVL_SlowZone::OnOverlapBegin);
	CollisionComponent->OnComponentEndOverlap.AddDynamic(this, &AVL_SlowZone::OnOverlapEnd);
	
	// Set material if provided
	if (ZoneMaterial)
	{
		CylinderMesh->SetMaterial(0, ZoneMaterial);
	}
	
	// Set timer for shrinking
	GetWorldTimerManager().SetTimer(DestroyTimerHandle, this, &AVL_SlowZone::StartShrinking, ZoneDuration, false);
}

// Called every frame
void AVL_SlowZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Update elapsed time
	ElapsedTime += DeltaTime;
	
	// Handle different states
	if (CurrentState == EZoneState::Growing)
	{
		// Calculate scale factor based on elapsed time
		float ScaleFactor = FMath::Min(ElapsedTime / GrowDuration, 1.0f) * MaxScale;
		
		// Apply scale to X and Y (radius), maintain Z scale to keep it flat
		SetActorScale3D(FVector(ScaleFactor, ScaleFactor, ScaleFactor));
		
		// If growth completed, transition to active state
		if (ElapsedTime >= GrowDuration)
		{
			CurrentState = EZoneState::Active;
			ElapsedTime = 0.0f;
		}
	}
	else if (CurrentState == EZoneState::Shrinking)
	{
		// Calculate scale factor based on elapsed time
		float ScaleFactor = FMath::Max(1.0f - (ElapsedTime / ShrinkDuration), 0.0f) * MaxScale;
		
		// Apply scale to X and Y (radius), maintain Z scale to keep it flat
		SetActorScale3D(FVector(ScaleFactor, ScaleFactor, ScaleFactor));
		
		// If shrinking completed, destroy the actor
		if (ElapsedTime >= ShrinkDuration)
		{
			Destroy();
		}
	}
}

void AVL_SlowZone::StartShrinking()
{
	// Reset timer and set state to shrinking
	CurrentState = EZoneState::Shrinking;
	ElapsedTime = 0.0f;
}
