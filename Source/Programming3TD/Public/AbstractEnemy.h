// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <BuildingSlot.h>
#include "AbstractEnemy.generated.h"

class USphereComponent;

UCLASS(Abstract)
class PROGRAMMING3TD_API AAbstractEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAbstractEnemy();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<USphereComponent> OverlapSphere;

protected:
	/*
	* An array of nodes the enemy will traverse.
	* 
	* Don't change elements of this array directly, in case Unreal Engine
	* does not make a clone of the array.
	*/
	UPROPERTY(BlueprintReadWrite)
	TArray<TObjectPtr<ABuildingSlot>> pathQueue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 healthCurrent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 healthMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 queueIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isAlive;

public:
	void SetPathQueue(TArray<TObjectPtr<ABuildingSlot>> PathQueue);

	/*
	* Function to attack this enemy.
	* 
	* @return true if the enemy is killed, false otherwise.
	*/
	virtual bool AttackThis(int32 damage);

	/*
	* Function to spawn this enemy.
	* Called by wave manager when the enemy is spawned.
	*/
	void Spawn();

};
