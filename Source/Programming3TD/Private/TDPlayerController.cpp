#include "TDPlayerController.h"
#include "TDPlayerController.h"
// Fill out your copyright notice in the Description page of Project Settings.


#include "TDPlayerController.h"
#include "TDPlayerCharacter.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

ATDPlayerController::ATDPlayerController()
{
	HPCurrent = 100;
	HPMax = 100;
	WaveManager = nullptr;
}

void ATDPlayerController::SetWaveManager(AAbstractWaveManager* newWaveManager)
{
	if (HasWaveManager()) return; // must reset if you change the wave manager
	WaveManager = newWaveManager;
}

bool ATDPlayerController::HasWaveManager() const
{
	return WaveManager != nullptr;
}

void ATDPlayerController::Reset()
{
	WaveManager = nullptr;
	HPCurrent = HPMax;
}

int64 ATDPlayerController::GetHPCurrent() const
{
	return HPCurrent;
}

int64 ATDPlayerController::GetHPMax() const
{
	return HPMax;
}

void ATDPlayerController::SetMaxHP(int64 newMaxHP)
{
	HPMax = newMaxHP;
	if (HPCurrent > HPMax) HPCurrent = HPMax;
}

void ATDPlayerController::LoseHealth(int64 DamageTaken)
{
	if (DamageTaken <= 0)
		return;

	HPCurrent -= DamageTaken;
	if (GetHPCurrent() <= 0)
	{
		LoseGame();
	}
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("still hanging on"));
}

void ATDPlayerController::LoseGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), UGameplayStatics::GetPlayerController(GetWorld(), 0), EQuitPreference::Quit, true);
}

bool ATDPlayerController::GetIsWaveActive() const
{
	return WaveManager->bIsWaveActive;
}

void ATDPlayerController::StartWave()
{
	if (!HasWaveManager())
	{
		return;
	}

	WaveManager->StartWave();
	Cast<ATDPlayerCharacter>(GetCharacter())->AddBuildableTowers();
}

void ATDPlayerController::AddDeadEnemyToWaveManager(AAbstractEnemy* deadEnemy)
{
	if (!HasWaveManager())
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("womp womp"));
		return;
	}

	WaveManager->AddDeadEnemy(deadEnemy);
}
