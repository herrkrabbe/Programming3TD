// Fill out your copyright notice in the Description page of Project Settings.


#include "AbstractWaveManager.h"
#include <Kismet/GameplayStatics.h>
#include <TDPlayerController.h>

// Sets default values
AAbstractWaveManager::AAbstractWaveManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAbstractWaveManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAbstractWaveManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAbstractWaveManager::StartWave()
{
	if (StartNode == nullptr || EndNode == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("StartNode is nullptr"));
		return;
	}

	if (bIsWaveActive) return; //can't start wave if wave is already active
	if (NewEnemiesQueue.IsEmpty()) return; //can't start a wave if the final wave has already been spawned

	//TODO: run pathfinding algorithm to find path from StartNode to EndNode

	//TODO: check if pathfinding algorithm was successful

	AddNewEnemiesToWave();
	EnemiesInWave = EnemiesInWaveStack.Num();

	bIsWaveActive = true;
}

void AAbstractWaveManager::EndWave()
{
	bIsWaveActive = false;

	// Get controller
	TObjectPtr<APlayerController> GenericController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	TObjectPtr<ATDPlayerController> TDController = Cast<ATDPlayerController>(GenericController.Get());

	if (TDController.IsNull()) return;

	// Tell the controller the wave has ended
	TDController.Get()->WaveEnded();

	// check if this was the final wave
	if (!NewEnemiesQueue.IsEmpty())
	{
		return;
	}

	// inform the controller that the game has ended
	TDController.Get()->GameEnded();
}

void AAbstractWaveManager::AddDeadEnemy(TObjectPtr<AAbstractEnemy> enemy)
{
	DeadEnemyStack.Push(enemy);

	enemy.Get()->TeleportGlobal(this->GetActorLocation());

	if (DeadEnemyStack.Num() != EnemiesInWave)
	{
		return;
	}

	EndWave();
}

void AAbstractWaveManager::AddNewEnemy(AAbstractEnemy* newEnemy)
{
	if (!bIsWaveActive) return;
	EnemiesInWaveStack.Push(newEnemy);
}

int64 AAbstractWaveManager::AddNewEnemiesToWave()
{
	if (NewEnemiesPerWave < 1) throw "NewEnemiesPerWave is less than 1";

	int64 enemiesAdded = 0;

	for (int i = 0; i < NewEnemiesPerWave; i++) {
		if (NewEnemiesQueue.IsEmpty()) {
			break;
		}

		DeadEnemyStack.Push(NewEnemiesQueue.First());
		NewEnemiesQueue.PopFirst();
		enemiesAdded++;
	}
	return enemiesAdded;
}

