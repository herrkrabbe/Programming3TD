// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <BuildingSlot.h>

#include <AbstractEnemy.h>
#include "AbstractWaveManager.generated.h"

UCLASS(Abstract)
class PROGRAMMING3TD_API AAbstractWaveManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAbstractWaveManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:
	/*
	* Enemies to be spawned this wave.
	* Enemies are spawned in the order they are in the stack.

	*/
	TArray<TObjectPtr<AAbstractEnemy>> EnemiesInWaveStack;

	/*
	* When an enemy dies, it is added to the DeadEnemyStack.
	* 
	* The enemies for next wave are added to the bottom of this stack
	* at the beginning of a wave.
	* 
	* WARNING: do not compare the size of this stack to EnemiesInWave because of
	* the aformentioned reason.
	* 
	* This stack becomes EnemiesInWaveStack at the end of the wave, to prepare
	* for the next wave.
	*/
	TArray<TObjectPtr<AAbstractEnemy>> DeadEnemyStack;

	/*
	* The number of enemies in the wave. Value is set at the beginning of the game
	and at the end of every wave.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave", meta = (AllowPrivateAccess = "true"))
	int64 EnemiesInWave = 2;

	/*
	* Is the wave ongoing?
	*/
	UPROPERTY(BlueprintReadWrite, Category = "Wave", meta = (AllowPrivateAccess = "true"))
	bool bIsWaveActive = false;

public:

	bool GetIsWaveActive() {
		return bIsWaveActive;
	}

	/*
	* The BuildingSlot where the enemies spawn.
	*/
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<ABuildingSlot> StartNode = nullptr;

	/*
	* The BuildingSlot where the enemies go.
	*/
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<ABuildingSlot> EndNode = nullptr;

	/*
	* Function to start a wave. Can be called by the player.
	* 
	* Wave will not start if there is no given EndNode and StartNode.
	*/
	virtual void StartWave();

	/*
	* Function to end a wave. Should only be called by the wavemanager,
	* unless the player wants to end the wave prematurely (such as exiting the game).
	*/
	virtual void EndWave();

	/*
	* Function to add an enemy to the DeadEnemyStack. Called by the playercontroller.
	*/
	void AddDeadEnemy(TObjectPtr<AActor> enemy);
};
