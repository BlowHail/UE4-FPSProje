// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FPSHUD.generated.h"

/**
 * 
 */
UCLASS()
class FPSPROJECT_API AFPSHUD : public AHUD
{
	GENERATED_BODY()
	
	public:
		virtual void DrawHUD() override;

protected:
		//在屏幕中央绘制
		UPROPERTY(EditDefaultsOnly)
		UTexture2D* CrosshairTexture;
};
