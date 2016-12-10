// Fill out your copyright notice in the Description page of Project Settings.

#include "BatteryCollector.h"
#include "BatteryPickup.h"

ABatteryPickup::ABatteryPickup(){
	//ʹ����ģ���������
	GetMesh()->SetSimulatePhysics(true);

	BatteryPower = 150.f;
}

void ABatteryPickup::wasCollected_Implementation(){
	//ʹ�û���Ĺ���
	//��Super����д
	Super::wasCollected_Implementation();
	//�ռ�����յ��
	Destroy();
}
//��ʾ��ǰ������ֵ
float ABatteryPickup::GetPower(){
	return BatteryPower;
}
