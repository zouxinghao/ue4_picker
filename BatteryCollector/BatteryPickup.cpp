// Fill out your copyright notice in the Description page of Project Settings.

#include "BatteryCollector.h"
#include "BatteryPickup.h"

ABatteryPickup::ABatteryPickup(){
	//使物体模拟物理过程
	GetMesh()->SetSimulatePhysics(true);

	BatteryPower = 150.f;
}

void ABatteryPickup::wasCollected_Implementation(){
	//使用基类的功能
	//用Super来重写
	Super::wasCollected_Implementation();
	//收集后清空电池
	Destroy();
}
//显示当前的能量值
float ABatteryPickup::GetPower(){
	return BatteryPower;
}
