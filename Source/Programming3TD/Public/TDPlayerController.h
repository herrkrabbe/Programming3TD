// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include <AbstractWaveManager.h>
#include "TDPlayerController.generated.h"


/**
 * 
 */
UCLASS()
class PROGRAMMING3TD_API ATDPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	int64 HPCurrent;
	int64 HPMax;
	TObjectPtr<AAbstractWaveManager> WaveManager;	

public:
	ATDPlayerController();

	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetWaveManager(AAbstractWaveManager* newWaveManager);

	UFUNCTION(BlueprintCallable, Category = "Getters")
	bool HasWaveManager() const;

	UFUNCTION(BlueprintCallable, Category = "New Wave")
	void Reset();

	UFUNCTION(BlueprintCallable, Category = "Getters")
	int64 GetHPCurrent() const;

	UFUNCTION(BlueprintCallable, Category = "Getters")
	int64 GetHPMax() const;

	UFUNCTION(BlueprintCallable, Category = "Setters")
	void SetMaxHP(int64 newMaxHP);

	UFUNCTION(BlueprintCallable, Category = "Damage")
	void LoseHealth(int64 DamageTaken);

	UFUNCTION(BlueprintCallable, /*BlueprintNativeEvent,*/ Category = "Damage")
	void LoseGame();
	
	/*
	* Function called to tell the controller the wave has ended
	*/
	UFUNCTION(BlueprintImplementableEvent, Category = "Game")
	void WaveEnded();

	UFUNCTION(BlueprintImplementableEvent, Category = "Game")
	void GameEnded();

	/*
	* Tells wave manager to start the wave.
	*/
	UFUNCTION(BlueprintCallable, Category = "Game")
	void StartWave();

	/*
	* Adds a dead enemy to the wave manager.
	* 
	* This function exists for enemies to quickly inform the wave manager they have died
	* without needint to know the wave manager's reference.
	*/
	UFUNCTION(BlueprintCallable, Category = "Running")
	void AddDeadEnemyToWaveManager(AAbstractEnemy* deadEnemy);
};
