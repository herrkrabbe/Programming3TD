// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbstractEnemy.h"
#include "BigEnemy.generated.h"

/**
 * 
 */
UCLASS()
class PROGRAMMING3TD_API ABigEnemy : public AAbstractEnemy
{
	GENERATED_BODY()

public:
	ABigEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
