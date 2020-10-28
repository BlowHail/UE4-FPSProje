// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class FPSPROJECT_API AFPSProjectile : public AActor
{
	GENERATED_BODY()

public:
	// 设置该 actor 属性的默认值
	AFPSProjectile();

protected:
	// 游戏开始时或生成时调用
	virtual void BeginPlay() override;

public:
	// 每帧调用
	virtual void Tick(float DeltaSeconds) override;

	// 球体碰撞组件。
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	USphereComponent* CollisionComponent;

	// 发射物运动组件。
	UPROPERTY(VisibleAnywhere, Category = Movement)
	UProjectileMovementComponent* ProjectileMovementComponent;

	// 在发射方向上设置发射物初速度的函数。
	void FireInDirection(const FVector& ShootDirection);

	// 发射物命中物体时调用的函数。
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

};