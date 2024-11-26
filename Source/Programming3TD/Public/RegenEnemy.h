// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbstractEnemy.h"
#include "RegenEnemy.generated.h"

/**
 * @Author Paulius
 */

UCLASS()
class PROGRAMMING3TD_API ARegenEnemy : public AAbstractEnemy
{
	GENERATED_BODY()


public:
	ARegenEnemy();
	
	virtual void Tick(float deltatime) override;
protected:
	// Called when the game starts or when spawned

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	void RegenHP();
	
protected:

	//int number for regen -healthregen
	int64 healthRegen;
	//Integer Placeholder for new hp value -healthregen
	int64 AfterRegenHP;

private:
	

};
