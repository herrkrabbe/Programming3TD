// Fill out your copyright notice in the Description page of Project Settings.


#include "BigEnemy.h"

ABigEnemy::ABigEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
	queueIndex = 0;
	isAlive = false;
	speed = 100;
	healthMax = 5;
	healthCurrent = healthMax;
	DamageDealt = 15;
}
