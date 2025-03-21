// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "VL_Projectile.generated.h"

UCLASS(config=Game)
class VALORANT_LIKE_API AVL_Projectile : public AActor
{
	GENERATED_BODY()

	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
	USphereComponent* CollisionComp;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;
	
protected:	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile)
	int Damage = 0;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile)
	int32 MaxBounces = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile)
	int32 BounceCount = 0;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Projectile)
	TSubclassOf<class AVL_SlowZone> SlowZoneClass;
	
	
	UPROPERTY(EditDefaultsOnly, Category="Abilities")
	TSubclassOf<UVL_SlowZoneAbility> SlowZoneAbilityClass;

public:
	AVL_Projectile();
	
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBounce(const FHitResult& ImpactResult, const FVector& ImpactVelocity);

	/** called when projectile hits something */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/** Returns CollisionComp subobject **/
	USphereComponent* GetCollisionComp() const;
	/** Returns ProjectileMovement subobject **/
	UProjectileMovementComponent* GetProjectileMovement() const;

	void SetDamage(int NewDamage);
	
	void SetMaxBoundCount(int MaxBounds);

	bool bIsSlowProjectile = false;

private:
	UPROPERTY(VisibleAnywhere, Category="Attributes")
	UVL_SlowZoneAbility* SlowZoneAbility;
};
