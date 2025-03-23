// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "VL_SlowZone.generated.h"

UCLASS()
class VALORANT_LIKE_API AVL_SlowZone : public AActor
{
	GENERATED_BODY()public:	
	
	AVL_SlowZone();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* CylinderMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCapsuleComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UParticleSystemComponent* EffectComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
	UMaterialInterface* ZoneMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	float SlowAmount; // % between 0 and 1

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	float ZoneDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	float GrowDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	float ShrinkDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	float MaxScale;

private:
	FTimerHandle DestroyTimerHandle;

	enum class EZoneState : uint8
	{
		Growing,
		Active,
		Shrinking
	};
	EZoneState CurrentState;

	float ElapsedTime;

	UFUNCTION()
	void StartShrinking();

	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex);

};
