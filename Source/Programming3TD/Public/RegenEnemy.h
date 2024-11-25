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

	//AAbstractEnemy();
	ARegenEnemy();

public:

	 
	
protected:
	// Called when the game starts or when spawned

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
protected:

	//Integer for HPRegen
	int64 healthRegen;
	//Integer Placeholder for new hp value
	int64 AfterRegenHP; 

private:
	void RegenHP();

};
