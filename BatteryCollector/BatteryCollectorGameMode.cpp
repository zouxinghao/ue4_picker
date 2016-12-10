// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "BatteryCollector.h"
#include "BatteryCollectorGameMode.h"
#include "BatteryCollectorCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "SpawnVolume.h"

ABatteryCollectorGameMode::ABatteryCollectorGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	DecayRate = 0.01f;
}

//吧BeginPlay（）放在这个位置，因为他要在TIck系统开始之前
void ABatteryCollectorGameMode::BeginPlay(){
	Super::BeginPlay();

	//找到所有要下落的物体，在状态确认好了以后
	TArray<AActor*>FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundActors);
	for (auto Actor : FoundActors){
		ASpawnVolume* SpawnVolumeActor = Cast<ASpawnVolume>(Actor);
		if (SpawnVolumeActor){
			SpawnVolumeActors.AddUnique(SpawnVolumeActor);
		}
	}
	SetCurrentState(EBatteryPlayState::EPlaying);

	ABatteryCollectorCharacter* MyCharacter = Cast<ABatteryCollectorCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (MyCharacter){
		PowerToWin = (MyCharacter->GetInitialPower())*1.25;
		if (HUDWidgetClass != nullptr){
			CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
			if (CurrentWidget !=nullptr)
			{
				CurrentWidget->AddToViewport();
			}
		}
	}


}

void ABatteryCollectorGameMode::Tick(float DeltaTime){

	Super::Tick(DeltaTime);//应该是用时间来衡量量度（反正就那个意思:)）

	ABatteryCollectorCharacter* MyCharacter = Cast<ABatteryCollectorCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (MyCharacter)
	{
		if (MyCharacter->GetCurrentPower()>PowerToWin)
		{
			SetCurrentState(EBatteryPlayState::EWon);
		}
		else if (MyCharacter->GetCurrentPower()>100)
		{
			MyCharacter->UpdateCurrentPower(-DecayRate*DeltaTime*MyCharacter->GetCurrentPower());
		}
		else {
			SetCurrentState(EBatteryPlayState::EGameOver);
		}
	}
}

float ABatteryCollectorGameMode::GetPowerToWin() const{
	return PowerToWin;
}

EBatteryPlayState ABatteryCollectorGameMode::GetCurrentState() const{
	return CurrentState;
}

void ABatteryCollectorGameMode::SetCurrentState(EBatteryPlayState NewState){
	CurrentState = NewState;
	HandleNewState(CurrentState);
}

void ABatteryCollectorGameMode::HandleNewState(EBatteryPlayState NewState){
	switch (NewState){
	case EBatteryPlayState::EPlaying:{
		 for (ASpawnVolume* Volume : SpawnVolumeActors){
			 Volume->setSpawnVolumeActive(true);
		 }
	}

		break;
	case EBatteryPlayState::EWon:{
	 for (ASpawnVolume* Volume : SpawnVolumeActors){
		 Volume->setSpawnVolumeActive(false);
	 }

	}

		break;
	case EBatteryPlayState::EGameOver:{
	  for (ASpawnVolume* Volume : SpawnVolumeActors){
		  Volume->setSpawnVolumeActive(false);
	  }
	  APlayerController* PlayController = UGameplayStatics::GetPlayerController(this, 0);
	  if (PlayController){
		  PlayController->SetCinematicMode(true, false, false, true, true);
	  }
	  ACharacter* MyCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
	  if (MyCharacter){
		  MyCharacter->GetMesh()->SetSimulatePhysics(true);
		  MyCharacter->GetMovementComponent()->MovementState.bCanJump = false;
	  }

	}
		break;
	case EBatteryPlayState::EUnkonwn:{

	}

		break;
	}
}
