// Fill out your copyright notice in the Description page of Project Settings.


#include "RegenEnemy.h"

ARegenEnemy::ARegenEnemy() : AAbstractEnemy()
{

}

void ARegenEnemy::BeginPlay()
{
	Super::BeginPlay();

	healthCurrent = 3;
	healthMax = healthCurrent;
	healthRegen = 1;
	void regenHP();
}

void ARegenEnemy::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	//precaution
	pathQueue.Empty();
}


void ARegenEnemy::RegenHP() 
{
	//holds value og regen+hp
	AfterRegenHP = healthCurrent + healthRegen;
	
	if (AfterRegenHP >= healthMax)
	{
		healthCurrent = healthMax;
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, TEXT("Health is max"));
		return;
	}
	healthCurrent = AfterRegenHP;
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, TEXT("Recovered health"));

}
