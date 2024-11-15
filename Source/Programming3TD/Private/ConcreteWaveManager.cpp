// Fill out your copyright notice in the Description page of Project Settings.


#include "ConcreteWaveManager.h"


AConcreteWaveManager::AConcreteWaveManager()
{
   
}

void AConcreteWaveManager::BeginPlay() 
{
    Super::BeginPlay(); //spawns the function from AAbstractWaveManager

    //to do: spawn enmies, add enms to q, move enemies to start locations 
    // ~~ spawned under the floor) (maybe better to just have them at start location, only invisible,)
    // --enemies in q to the start of the level

    UE_LOG(LogTemp, Warning, TEXT("BeginPlay called in AConcreteWaveManager!"));
}


void AConcreteWaveManager::EndPlay()
{
    Super::EndPlay();
    // remove all enemies. remove queues-- 
    // empty path.q, empty newenemy.q, enemies in wavestack, dead enemy.stack 

    UE_LOG(LogTemp, Warning, TEXT("EndPlay called in AConcreteWaveManager!"));
}