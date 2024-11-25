// Fill out your copyright notice in the Description page of Project Settings.


#include "RegenEnemy.h"

void ARegenEnemy::ARegenEnemy()
{

}

void ARegenEnemy::BeginPlay()
{
	healthCurrent = 3;
	healthMax = healthCurrent;
	healthRegen = 1;
	void regenHP();
}

void ARegenEnemy::RegenHP() 
{
	healthCurrent*;
	AfterRegenHP = healthCurrent + healthRegen;
	AfterRegenHP = healthCurrent*;
}
