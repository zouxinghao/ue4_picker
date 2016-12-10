// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

UCLASS()
class BATTERYCOLLECTOR_API APickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickup();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	//����ռ�����battery����ɫ����ɫ������ı䣬��������������ؽ�ɫ
	FORCEINLINE class UStaticMeshComponent* GetMesh() const{ return PickupMesh; }
	/*ע��UFUNCTION������*/

	/*
	Pure & Callable:
	���߶����Ա�ʾ���function���Ա���ͼcall
	���𣺿�����û����������ͷ��һ��API��
	*/

	//�����������Ƿ���active
	UFUNCTION(BlueprintPure,Category="Pickup")
	bool IsActive();
	//��������������ȫ�ظı��Ƿ���active
	UFUNCTION(BlueprintCallable,Category="Pickup")
	void SetActive(bool NewPickupState);

	//���������Ƿ��Ѿ����ռ�����
	//���麯�����������Ӻ������汻��д
	UFUNCTION(BlueprintNativeEvent)
		//�ù��ܵ�Ŀ����ͨ��һ����ͼ�����ǣ���Ҳ�б���ʵ�֡��ṩ��һ����Ϊ
		//[������]_Implementation�ı������[������]���ڱ�Ҫʱ�Զ����ɵĴ��뽫����һ��thunk���õ�ʵ�ַ�����
	void wasCollected();
	void virtual wasCollected_Implementation();

protected:
	//ΪtrueʱPickup���Ա�����
	bool bIsActive;

private://����Mesh�Ķ��塢��������private����������������ͼ�Ȳ��ɷ���
	//PROPERTY:���ԡ�����
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Pickup",meta=(AllowPrivateAccess="true"))
	class UStaticMeshComponent* PickupMesh;
	
};
