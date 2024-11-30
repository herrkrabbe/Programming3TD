// Fill out your copyright notice in the Description page of Project Settings.


#include "RegenEnemy.h"

ARegenEnemy::ARegenEnemy() : AAbstractEnemy()
{
}

void ARegenEnemy::Tick(float deltatime)
{
	Super::Tick(deltatime);
	if (!isAlive)
		return;
	
	RegenHP(deltatime);
}

void ARegenEnemy::BeginPlay()
{
	Super::BeginPlay();
	queueIndex = 0;
	isAlive = false;
	healthMax = 3;
	healthCurrent= healthMax;
	healthRegen = 1;
	DamageDealt = 4;
	RegenTimer = 1;

}

void ARegenEnemy::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	//precaution
	pathQueue.Empty();
}


void ARegenEnemy::RegenHP(float deltaTime) 
{
	if (healthCurrent == healthMax)
	{
		//holds value og regen+hp

		return;
	}
	
	float HealthRegained = healthRegen * deltaTime;
	AfterRegenHP = healthCurrent + HealthRegained;

	
	if (AfterRegenHP > healthMax)
	{
		healthCurrent = healthMax;
		return;
	}

	healthCurrent = AfterRegenHP;
	HPBar->UpdateHPBar(healthCurrent, healthMax);
}
