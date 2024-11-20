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
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;


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
	* The number of enemies in the wave. Value is set at the beginning of every wave.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave", meta = (AllowPrivateAccess = "true"))
	int64 EnemiesInWave;

	/*
	* Is the wave ongoing?
	*/
	UPROPERTY(BlueprintReadWrite, Category = "Wave", meta = (AllowPrivateAccess = "true"))
	bool bIsWaveActive = false;

	TDeque<TObjectPtr<AGraphNode>> Path;


	float TimeUntilSpawn;
	float SpawnRateInSeconds = 2.0f;


protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wave")
	int64 NewEnemiesPerWave = 2;

	TDeque<TObjectPtr<AAbstractEnemy>> NewEnemiesQueue;

public:

	bool GetIsWaveActive() {
		return bIsWaveActive;
	}

	/*
	* The BuildingSlot where the enemies spawn.
	*/
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<AGraphNode> StartNode = nullptr;

	/*
	* The BuildingSlot where the enemies go.
	*/
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<AGraphNode> EndNode = nullptr;

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
	void AddDeadEnemy(TObjectPtr<AAbstractEnemy> enemy);

	/*
	* Adds a new enemy to the NewEnemyQueue, but only if the wave is not running.
	*/
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void AddNewEnemy(AAbstractEnemy* newEnemy);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void AddNewEnemyFromClass(TSubclassOf<AAbstractEnemy> enemyClass);

	/*
	* A test function to spawn an enemy.
	* Adds the enemy to the EnemiesInWaveStack and immediately spawns it.
	*/
	UFUNCTION(BlueprintCallable, Category="Prototyping")
	void SpawnEnemyPrototypeFunction(AAbstractEnemy* enemy);

	/*
	* Creates and sets the Path.
	* 
	* @return True if the path was created successfully.
	* @return False if the path could not be created.
	*/
	UFUNCTION(BlueprintCallable, Category = "Setup")
	bool CreatePath();

private:
	int64 AddNewEnemiesToWave();

	/*
	* Sets the path of the next enemy and then spawns it.
	*/
	void SpawnNextEnemy();
};