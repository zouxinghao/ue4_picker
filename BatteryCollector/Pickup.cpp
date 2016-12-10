// Fill out your copyright notice in the Description page of Project Settings.

#include "BatteryCollector.h"
#include "Pickup.h"


// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	//所有的Pickup动作可以被进行
	//在这一步可以设置：比如在某某事件放生以后Pickip才可以进行
	bIsActive = true;
	
	//创建角色
	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	RootComponent = PickupMesh;
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickup::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

//return active state
bool APickup::IsActive(){
	return bIsActive;
}

//change active state
void APickup::SetActive(bool NewPickupState){
	bIsActive = NewPickupState;
}

void APickup::wasCollected_Implementation(){
	//打印debug的log
	FString PickupDebugString = GetName();
	UE_LOG(LogClass, Log, TEXT("The Collected was %s"), *PickupDebugString);
}

