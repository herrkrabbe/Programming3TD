// Fill out your copyright notice in the Description page of Project Settings.


#include "BigEnemy.h"

ABigEnemy::ABigEnemy() : AAbstractEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
	queueIndex = 0;
	isAlive = false;
	healthMax = 5;
	healthCurrent = healthMax;
	DamageDealt = 15;
}

void ABigEnemy::BeginPlay()
{
	Super::BeginPlay();
	queueIndex = 0;
	isAlive = false;
	healthMax = 5;
	healthCurrent = healthMax;
	DamageDealt = 15;
}

void ABigEnemy::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ABigEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
