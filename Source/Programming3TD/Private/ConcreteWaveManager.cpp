// Fill out your copyright notice in the Description page of Project Settings.


#include "ConcreteWaveManager.h"


AConcreteWaveManager::AConcreteWaveManager()
{
    // Set default values for this component
    PrimaryComponentTick.bCanEverTick = true;
}



void AConcreteWaveManager::BeginPlay()
{
    Super::BeginPlay(); // Always call the base class's BeginPlay first

    // Your custom initialization logic here
    UE_LOG(LogTemp, Warning, TEXT("BeginPlay called in AConcreteWaveManager!"));
}

void AConcreteWaveManager::EndPlay()
{
    Super::EndPlay(); // Always call the base class's BeginPlay first

    // Your custom initialization logic here
    UE_LOG(LogTemp, Warning, TEXT("EndPlay called in AConcreteWaveManager!"));
}