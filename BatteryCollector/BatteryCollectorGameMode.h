// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
#include "BatteryCollectorGameMode.generated.h"

//游戏中可能出现的状态
UENUM(BlueprintType)
enum class EBatteryPlayState{
	EPlaying,
	EGameOver,
	EWon,
	EUnkonwn
};

UCLASS(minimalapi)
class ABatteryCollectorGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ABatteryCollectorGameMode();

	virtual void Tick(float DeltaTime) override;

	//返回赢得游戏所需的能量值——需要调用HUD
	UFUNCTION(BlueprintPure, Category = "Power")
	float GetPowerToWin() const;

	virtual void BeginPlay() override;

	//返回当前的状态
	UFUNCTION(BlueprintPure, Category = "Power")
		EBatteryPlayState GetCurrentState() const;

	void SetCurrentState(EBatteryPlayState NewState);
protected:
	//创建能量的下降率
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power",meta=(BlueprintProtected="true"))
	float DecayRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", meta = (BlueprintProtected = "true"))
	float PowerToWin;

	/** 项目栏*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", meta = (BlueprintProtected = "true"))
	TSubclassOf<class UUserWidget> HUDWidgetClass;

	/** 项目栏的接口*/
	UPROPERTY()
	class UUserWidget* CurrentWidget;

private:
	//追踪当前的游戏状态
	EBatteryPlayState CurrentState;

	TArray<class ASpawnVolume*>SpawnVolumeActors;

	void HandleNewState(EBatteryPlayState NewState);
};



