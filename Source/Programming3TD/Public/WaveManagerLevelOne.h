// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbstractWaveManager.h"
#include "WaveManagerLevelOne.generated.h"

/**
 * @author pauliepus
 */
UCLASS()
class PROGRAMMING3TD_API AWaveManagerLevelOne : public AAbstractWaveManager
{
	GENERATED_BODY()
	AWaveManagerLevelOne();

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;


private:
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemy Class")
	TSubclassOf<AAbstractEnemy> WeakEnemyClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Class")
	TSubclassOf<AAbstractEnemy> StrongEnemyClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Class")
	TSubclassOf<AAbstractEnemy> RegenEnemyClass;
};


