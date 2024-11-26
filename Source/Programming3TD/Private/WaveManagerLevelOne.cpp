// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveManagerLevelOne.h"


AWaveManagerLevelOne::AWaveManagerLevelOne() : AAbstractWaveManager()
{
   
}

void AWaveManagerLevelOne::BeginPlay() 
{
    Super::BeginPlay(); //calls the function from parent, i.e. AAbstractWaveManager
    

    //to do: spawn enmies, add enms to q, move enemies to start locations 
    // ~~ spawned under the floor) (maybe better to just have them at start location, only invisible,)
    // --enemies in q to the start of the level

    UE_LOG(LogTemp, Warning, TEXT("BeginPlay called in AWaveManagerLevelOne!"));
	//AddNewEnemyFromClass(RegenEnemyClass);
	AddNewEnemyFromClass(WeakEnemyClass);
	AddNewEnemyFromClass(WeakEnemyClass);
	AddNewEnemyFromClass(StrongEnemyClass);
	AddNewEnemyFromClass(StrongEnemyClass);
	AddNewEnemyFromClass(WeakEnemyClass);
	AddNewEnemyFromClass(StrongEnemyClass);
	AddNewEnemyFromClass(StrongEnemyClass);

}


void AWaveManagerLevelOne::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);
    // removes all enemies. remove queues
    // empty path.q, empty newenemy.q, enemies in wavestack, dead enemy.stack 

    UE_LOG(LogTemp, Warning, TEXT("EndPlay called in AWaveManagerLevelOne!"));
}