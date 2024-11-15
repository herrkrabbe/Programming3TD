// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbstractWaveManager.h"
#include "ConcreteWaveManager.generated.h"

/**
 * @author pauliepus
 */
UCLASS()
class PROGRAMMING3TD_API AConcreteWaveManager : public AAbstractWaveManager
{
	GENERATED_BODY()

private:

public:

protected:
	void BeginPlay();
	void EndPlay();
};

AConcreteWaveManager::BeginPlay() {
	Super::BeginPlay();
	//spawn enmies, add enms to q


}

AConcreteWaveManager::EndPlay() {
	//remove all enemies. remove queues-- 
	// empty path.q, empty newenemy.q, enemies in wavestack, dead enemy.stack 
	Super::EndPlay();

}
