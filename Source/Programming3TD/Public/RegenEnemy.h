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

	 
	
protected:
	// Called when the game starts or when spawned

	virtual void BeginPlay() override;


protected:

	//Integer for HPRegen
	int64 healthRegen;

	//Placeholder for new hp value
	int64 AfterRegenHP; 

public:
	
	void RegenHP();

};
