// Fill out your copyright notice in the Description page of Project Settings.


#include "RegenEnemy.h"

ARegenEnemy::ARegenEnemy() : AAbstractEnemy()
{
}

void ARegenEnemy::Tick(float deltatime)
{
	Super::Tick(deltatime);
	if(isAlive)
	RegenHP();
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

}

void ARegenEnemy::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	//precaution
	pathQueue.Empty();
}


void ARegenEnemy::RegenHP() 
{
	if (healthCurrent == healthMax)
	{
		//holds value og regen+hp

		return;
	}
	
	AfterRegenHP = healthCurrent + healthRegen;
	
	if (AfterRegenHP >= healthMax)
	{
		healthCurrent = healthMax;
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, TEXT("Health is max cant heal"));
		return;
	}

	healthCurrent = AfterRegenHP;
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, TEXT("Recovered health"));

}
