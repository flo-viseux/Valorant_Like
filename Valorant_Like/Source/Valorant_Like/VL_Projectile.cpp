// Fill out your copyright notice in the Description page of Project Settings.


#include "VL_Projectile.h"

#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AVL_Projectile::AVL_Projectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USphereComponent* CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->InitSphereRadius(5.0f);
	CollisionComponent->SetCollisionProfileName("Projectile");
	RootComponent = CollisionComponent;
	CollisionComponent->OnComponentHit.AddDynamic(this, &AVL_Projectile::OnHit);
}

// Called when the game starts or when spawned
void AVL_Projectile::BeginPlay()
{
	Super::BeginPlay();
}

void AVL_Projectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor != GetOwner())
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, GetOwner()->GetInstigatorController(), this, UDamageType::StaticClass());
		Destroy();
	}
}

