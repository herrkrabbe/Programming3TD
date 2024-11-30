// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveManagerLevelOne.h"


AWaveManagerLevelOne::AWaveManagerLevelOne() : AAbstractWaveManager()
{
   
}

void AWaveManagerLevelOne::BeginPlay() 
{
    Super::BeginPlay(); //calls the function from parent, i.e. AAbstractWaveManager

	// add enemies to the queue
	AddNewEnemyFromClass(WeakEnemyClass);
	AddNewEnemyFromClass(WeakEnemyClass);
	AddNewEnemyFromClass(WeakEnemyClass);
	AddNewEnemyFromClass(StrongEnemyClass);
	AddNewEnemyFromClass(RegenEnemyClass);
	AddNewEnemyFromClass(WeakEnemyClass);
	AddNewEnemyFromClass(StrongEnemyClass);
	AddNewEnemyFromClass(StrongEnemyClass);

}


void AWaveManagerLevelOne::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);
    // removes all enemies. remove queues
    // empty path.q, empty newenemy.q, enemies in wavestack, dead enemy.stack 

}