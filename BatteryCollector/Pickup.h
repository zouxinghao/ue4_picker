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

	//如果收集到了battery，角色的颜色会放生改变，用这个函数来返回角色
	FORCEINLINE class UStaticMeshComponent* GetMesh() const{ return PickupMesh; }
	/*注意UFUNCTION的作用*/

	/*
	Pure & Callable:
	两者都可以表示这个function可以被蓝图call
	区别：看视屏没有听懂，回头看一下API吧
	*/

	//看返回类型是否是active
	UFUNCTION(BlueprintPure,Category="Pickup")
	bool IsActive();
	//允许其他类来安全地改变是否是active
	UFUNCTION(BlueprintCallable,Category="Pickup")
	void SetActive(bool NewPickupState);

	//检验物体是否已经被收集到了
	//用虚函数，可以在子函数里面被重写
	UFUNCTION(BlueprintNativeEvent)
		//该功能的目的是通过一个蓝图来覆盖，但也有本地实现。提供了一个名为
		//[函数名]_Implementation的本体而非[函数名]；在必要时自动生成的代码将包括一个thunk调用的实现方法。
	void wasCollected();
	void virtual wasCollected_Implementation();

protected:
	//为true时Pickup可以被进行
	bool bIsActive;

private://将对Mesh的定义、操作放在private，可以让其他的蓝图等不可访问
	//PROPERTY:特性、属性
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Pickup",meta=(AllowPrivateAccess="true"))
	class UStaticMeshComponent* PickupMesh;
	
};
