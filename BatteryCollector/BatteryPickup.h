// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Pickup.h"
#include "BatteryPickup.generated.h"

/**
 * 
 */
UCLASS()
class BATTERYCOLLECTOR_API ABatteryPickup : public APickup
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ABatteryPickup();
	
	//��дwasCollected(),����Implememtation����Ϊ�ڶ����ʱ������BlueprintNatveEvent
	void wasCollected_Implementation() override;
	
	/**A pulic way to accsess the power level**/
	float GetPower();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite,  Category = "Power",meta = (BlueprintProtected = "true"))
		float BatteryPower;
};
