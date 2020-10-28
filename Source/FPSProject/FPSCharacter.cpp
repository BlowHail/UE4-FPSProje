// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/Engine.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "FPSProjectile.h"
#include "FPSCharacter.h"

// 设置默认值
AFPSCharacter::AFPSCharacter()
{
	// 设置此角色每帧调用 Tick()。不需要时可将此关闭，以提高性能。
	PrimaryActorTick.bCanEverTick = true;

	// 创建一个第一人称摄像机组件。
	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	// 将摄像机组件附加到胶囊体组件。
	FPSCameraComponent->SetupAttachment((USceneComponent *)GetCapsuleComponent());
	// 将摄像机放置在眼睛上方不远处。
	FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));
	// 用 pawn 控制摄像机旋转。
	FPSCameraComponent->bUsePawnControlRotation = true;

	// 为拥有玩家创建一个第一人称模型组件。
	FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	// 该模型仅对拥有玩家可见。
	FPSMesh->SetOnlyOwnerSee(true);
	// 将 FPS 模型添加到 FPS 摄像机。
	FPSMesh->SetupAttachment(FPSCameraComponent);
	// 禁用部分环境阴影，保留单一模型存在的假象。
	FPSMesh->bCastDynamicShadow = false;
	FPSMesh->CastShadow = false;

	// 拥有玩家无法看到普通（第三人称）身体模型。
	GetMesh()->SetOwnerNoSee(true);
}

// 游戏开始时或生成时调用
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (GEngine)
	{
		// 显示调试信息五秒。-1"键"值（首个参数）说明我们无需更新或刷新此消息。
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using FPSCharacter."));
	}
}

// 每帧调用
void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// 调用后将功能绑定到输入
void AFPSCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 设置"移动"绑定。
	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRight);

	// 设置"查看"绑定。
	PlayerInputComponent->BindAxis("Turn", this, &AFPSCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AFPSCharacter::AddControllerPitchInput);

	// 设置"动作"绑定。
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFPSCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AFPSCharacter::StopJump);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFPSCharacter::Fire);
}

void AFPSCharacter::MoveForward(float Value)
{
	// 明确哪个方向是"前进"，并记录玩家试图向此方向移动。
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void AFPSCharacter::MoveRight(float Value)
{
	// 明确哪个方向是"向右"，并记录玩家试图向此方向移动。
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

void AFPSCharacter::StartJump()
{
	bPressedJump = true;
}

void AFPSCharacter::StopJump()
{
	bPressedJump = false;
}
void AFPSCharacter::Fire()
{
	//发射物体
	if (ProjectileClass)
	{
		//摄像机变换
		FVector CameraLocation;
		FRotator CameraRotation;
		GetActorEyesViewPoint(CameraLocation, CameraRotation);

		FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);
		FRotator MuzzleRotation = CameraRotation;
		//上抬准星
		MuzzleRotation.Pitch += 10.0f;
		UWorld* World = GetWorld();
		if (World) {
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = this;
			//生成发射物
			AFPSProjectile* Projectile = World->SpawnActor<AFPSProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
			if (Projectile) {
				//设置发射物初始轨道
				FVector LaunchDirection = MuzzleRotation.Vector();
				Projectile->FireInDirection(LaunchDirection);
			}
		}
	}
}
