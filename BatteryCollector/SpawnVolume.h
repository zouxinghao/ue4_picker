// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

UCLASS()
class BATTERYCOLLECTOR_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnVolume();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	FORCENOINLINE class UBoxComponent* GetWhereToSpawn() { return WhereToSpawn; }

	//��������������һ����
	UFUNCTION(BlueprintPure, Category = "Spawning")
	FVector  GetRandomPointInVolum();

	UFUNCTION(BlueprintCallable, Category = "Spawning")
		void setSpawnVolumeActive(bool bShouldSpawn);

protected:
	UPROPERTY(EditAnywhere, Category = "Spwaning")
		TSubclassOf<class APickup> WhatToSpawn;

	FTimerHandle SpawnTimer;
	//��������ʱ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float SpawnDelayRangeLow;

	//��������ʱ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float SpawnDelayRangeHigh;

		
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* WhereToSpawn;


	//�������µ�����
	void SpawnPickup();
	
	float SpawnDelay;
};
