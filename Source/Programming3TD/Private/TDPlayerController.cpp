// Fill out your copyright notice in the Description page of Project Settings.


#include "TDPlayerController.h"

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
	return !(WaveManager.IsNull());
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

void ATDPlayerController::AddDeadEnemyToWaveManager(AAbstractEnemy* deadEnemy)
{
	if (!HasWaveManager())
	{
		return;
	}

	WaveManager->AddDeadEnemy(deadEnemy);
}
