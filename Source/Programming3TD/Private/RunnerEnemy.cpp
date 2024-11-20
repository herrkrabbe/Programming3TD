// Fill out your copyright notice in the Description page of Project Settings.


#include "RunnerEnemy.h"

ARunnerEnemy::ARunnerEnemy() : AAbstractEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
	queueIndex = 0;
	isAlive = false;
	healthMax = 1;
	healthCurrent = healthMax;
	DamageDealt = 3;
}

void ARunnerEnemy::BeginPlay()
{
	Super::BeginPlay();
	queueIndex = 0;
	isAlive = false;
	healthMax = 1;
	healthCurrent = healthMax;
	DamageDealt = 3;
}

void ARunnerEnemy::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ARunnerEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
