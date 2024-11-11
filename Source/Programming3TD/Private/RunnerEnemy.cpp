// Fill out your copyright notice in the Description page of Project Settings.


#include "RunnerEnemy.h"

ARunnerEnemy::ARunnerEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
	queueIndex = 0;
	isAlive = false;
	healthMax = 1;
	healthCurrent = healthMax;
	DamageDealt = 3;
}
