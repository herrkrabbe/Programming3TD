// Fill out your copyright notice in the Description page of Project Settings.


#include "AbstractWaveManager.h"

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
}

void AAbstractWaveManager::EndWave()
{
}

void AAbstractWaveManager::AddDeadEnemy(TObjectPtr<AActor> enemy)
{
}

