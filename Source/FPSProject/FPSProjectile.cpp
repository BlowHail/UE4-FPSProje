// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSProject.h"
#include "FPSProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AFPSProjectile::AFPSProjectile()
{
	// 将此 actor 设为每帧调用 Tick()。不需要时可将此关闭，以提高性能。
	PrimaryActorTick.bCanEverTick = true;

	// 使用球体代表简单碰撞。
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
	CollisionComponent->OnComponentHit.AddDynamic(this, &AFPSProjectile::OnHit);

	// 设置球体的碰撞半径。
	CollisionComponent->InitSphereRadius(15.0f);
	// 将碰撞组件设为根组件。
	RootComponent = CollisionComponent;

	// 使用此组件驱动此发射物的运动。
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
	ProjectileMovementComponent->InitialSpeed = 3000.0f;
	ProjectileMovementComponent->MaxSpeed = 3000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->Bounciness = 0.3f;

	// 3 秒后消亡
	InitialLifeSpan = 3.0f;
}

// 游戏开始时或生成时调用
void AFPSProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// 每帧调用
void AFPSProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// 在发射方向上设置发射物初速度的函数。
void AFPSProjectile::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

// 发射物命中物体时调用的函数。
void AFPSProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != this && OtherComponent->IsSimulatingPhysics())
	{
		OtherComponent->AddImpulseAtLocation(ProjectileMovementComponent->Velocity * 100.0f, Hit.ImpactPoint);
	}
}