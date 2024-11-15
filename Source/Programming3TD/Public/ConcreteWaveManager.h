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
	AConcreteWaveManager();

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:

public:

};


