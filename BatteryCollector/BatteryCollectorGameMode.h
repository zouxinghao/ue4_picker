// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
#include "BatteryCollectorGameMode.generated.h"

//��Ϸ�п��ܳ��ֵ�״̬
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

	//����Ӯ����Ϸ���������ֵ������Ҫ����HUD
	UFUNCTION(BlueprintPure, Category = "Power")
	float GetPowerToWin() const;

	virtual void BeginPlay() override;

	//���ص�ǰ��״̬
	UFUNCTION(BlueprintPure, Category = "Power")
		EBatteryPlayState GetCurrentState() const;

	void SetCurrentState(EBatteryPlayState NewState);
protected:
	//�����������½���
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power",meta=(BlueprintProtected="true"))
	float DecayRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", meta = (BlueprintProtected = "true"))
	float PowerToWin;

	/** ��Ŀ��*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", meta = (BlueprintProtected = "true"))
	TSubclassOf<class UUserWidget> HUDWidgetClass;

	/** ��Ŀ���Ľӿ�*/
	UPROPERTY()
	class UUserWidget* CurrentWidget;

private:
	//׷�ٵ�ǰ����Ϸ״̬
	EBatteryPlayState CurrentState;

	TArray<class ASpawnVolume*>SpawnVolumeActors;

	void HandleNewState(EBatteryPlayState NewState);
};



