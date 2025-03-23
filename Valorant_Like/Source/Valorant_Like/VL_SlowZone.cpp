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
	CylinderMesh->SetRelativeScale3D(FVector(1.0f, .1f, 0.1f));
	
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
	SlowAmount = 0.1f; // 50% slow
	ZoneDuration = 5.0f;
	GrowDuration = 1.0f; 
	ShrinkDuration = 1.0f;
	MaxScale = 5.0f;
	
	// Set initial state
	CurrentState = EZoneState::Growing;
	ElapsedTime = 0.0f;
}

// Called when the game starts or when spawned
void AVL_SlowZone::BeginPlay()
{
	Super::BeginPlay();

	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AVL_SlowZone::OnOverlapBegin);
	CollisionComponent->OnComponentEndOverlap.AddDynamic(this, &AVL_SlowZone::OnOverlapEnd);
	
	// Set initial scale to 0
	SetActorScale3D(FVector(1.0f, 1.0f, 0.01f));
	
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

	ElapsedTime += DeltaTime;
	
	if (CurrentState == EZoneState::Growing)
	{
		float ScaleFactor = FMath::Min(ElapsedTime / GrowDuration, 1.0f) * MaxScale;
		
		SetActorScale3D(FVector(ScaleFactor, ScaleFactor, 0.01f));
		CollisionComponent->SetCapsuleRadius(10.0f * ScaleFactor);
		CollisionComponent->SetCapsuleHalfHeight(5000.0f * ScaleFactor);
		
		if (ElapsedTime >= GrowDuration)
		{
			CurrentState = EZoneState::Active;
			ElapsedTime = 0.0f;
		}
	}
	else if (CurrentState == EZoneState::Shrinking)
	{
		float ScaleFactor = FMath::Max(1.0f - (ElapsedTime / ShrinkDuration), 0.0f) * MaxScale;
		
		SetActorScale3D(FVector(ScaleFactor, ScaleFactor, 0.01f));
		CollisionComponent->SetCapsuleRadius(10.0f * ScaleFactor);
		CollisionComponent->SetCapsuleHalfHeight(5000.0f * ScaleFactor);
		
		if (ElapsedTime >= ShrinkDuration)
		{
			Destroy();
		}
	}
}

void AVL_SlowZone::StartShrinking()
{
	CurrentState = EZoneState::Shrinking;
	ElapsedTime = 0.0f;
}

void AVL_SlowZone::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AVL_FPSCharacter* Character = Cast<AVL_FPSCharacter>(OtherActor);
	if (Character && Character->GetAbilitySystemComponent())
	{
		FName SlowZoneID = FName(*FString::Printf(TEXT("SlowZone_%s"), *GetName()));
        
		Character->GetAbilitySystemComponent()->AddSpeedModifier(SlowZoneID, SlowAmount);
	}
}

void AVL_SlowZone::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AVL_FPSCharacter* Character = Cast<AVL_FPSCharacter>(OtherActor);
	if (Character && Character->GetAbilitySystemComponent())
	{
		FName SlowZoneID = FName(*FString::Printf(TEXT("SlowZone_%s"), *GetName()));
        
		Character->GetAbilitySystemComponent()->RemoveSpeedModifier(SlowZoneID);
	}
}
