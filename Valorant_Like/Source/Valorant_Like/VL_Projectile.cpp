// Fill out your copyright notice in the Description page of Project Settings.


#include "VL_Projectile.h"
#include "VL_SlowZoneAbility.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AVL_Projectile::AVL_Projectile()
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AVL_Projectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 5000.f;
	ProjectileMovement->MaxSpeed = 5000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
    ProjectileMovement->ProjectileGravityScale = 0.0f;
	ProjectileMovement->bInitialVelocityInLocalSpace = true;
	ProjectileMovement->OnProjectileBounce.AddDynamic(this, &AVL_Projectile::OnBounce);
	MaxBounces = 0;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void AVL_Projectile::BeginPlay()
{
    Super::BeginPlay();
	
	if (SlowZoneAbilityClass)
	{
		SlowZoneAbility = NewObject<UVL_SlowZoneAbility>(this, SlowZoneAbilityClass);
		SlowZoneAbility->Init();
		SlowZoneAbility->SlowZoneClass = SlowZoneClass;
	}
}

void AVL_Projectile::OnBounce(const FHitResult& ImpactResult, const FVector& ImpactVelocity)
{
	if (ImpactResult.ImpactNormal.Z > 0.7f || !bIsSlowProjectile)  // 0.7  = cos(45°) -> plane surface
	{
		BounceCount++;

		if (bIsSlowProjectile && SlowZoneAbility)
		{
			SlowZoneAbility->SlowZoneClass = SlowZoneClass;
			SlowZoneAbility->Activate(ImpactResult.Location, GetWorld());
		}
	}
    
	if (BounceCount > MaxBounces)
	{
		Destroy();
	}
}

void AVL_Projectile::SetMaxBoundCount(int MaxBoundsCount)
{
	MaxBounces = MaxBoundsCount;
}

void AVL_Projectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                           FVector NormalImpulse, const FHitResult& Hit)
{
	if (!bIsSlowProjectile)
	{
		// TODO : apply damage if is valid
	}
	
	if (OtherActor && OtherActor != GetOwner() && ProjectileMovement->bShouldBounce == false)
	{
		Destroy();
	}

	ProjectileMovement->ProjectileGravityScale = 1.0f;
}

USphereComponent* AVL_Projectile::GetCollisionComp() const
{
	return CollisionComp;
}

UProjectileMovementComponent* AVL_Projectile::GetProjectileMovement() const
{
	return ProjectileMovement;
}

void AVL_Projectile::SetDamage(int NewDamage)
{
	Damage = NewDamage;
}

