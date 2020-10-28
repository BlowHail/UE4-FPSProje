// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "FPSCharacter.generated.h"

UCLASS()
class FPSPROJECT_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// 设置该角色属性的默认值
	AFPSCharacter();

protected:
	// 游戏开始时或生成时调用
	virtual void BeginPlay() override;

public:
	// 每帧调用
	virtual void Tick(float DeltaSeconds) override;

	// 调用后将功能绑定到输入
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 处理前后移动的输入。
	UFUNCTION()
	void MoveForward(float Value);

	// 处理左右移动的输入。
	UFUNCTION()
	void MoveRight(float Value);

	// 按下按键时设置跳跃标记。
	UFUNCTION()
	void StartJump();

	// 松开按键时清除跳跃标记。
	UFUNCTION()
	void StopJump();

	// FPS 摄像机。
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* FPSCameraComponent;

	// 第一人称模型（手臂），仅对拥有玩家可见。
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* FPSMesh;
	// 处理开火的函数。
	UFUNCTION()
	void Fire();

	// 从摄像机位置的枪口偏移。 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;

	// 生成的发射物类。
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AFPSProjectile> ProjectileClass;
};