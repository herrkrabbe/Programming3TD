// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <GraphNode.h>
#include "Containers/Deque.h"

#include <EnemyHPBar.h>
#include "AbstractEnemy.generated.h"
class USphereComponent;
class UWidgetComponent;

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
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

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
	TDeque<TObjectPtr<AGraphNode>> pathQueue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float healthCurrent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float healthMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int64 DamageDealt;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int64 queueIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isAlive;

	//DO not set in blueprints
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HUD")
	UWidgetComponent* HPBarWidgetComponent;

	//pointer to the HPBar held by HPBarWidgetComponent. Used to update the HPBar.
	UEnemyHPBar* HPBar;

	UPROPERTY(EditAnywhere, Category = "HUD")
	TSubclassOf<UEnemyHPBar> HPBarClass;
private:
	FVector const HPBarPosition = FVector(0, 0, 100);

public:
	void SetPathQueue(TDeque<TObjectPtr<AGraphNode>> PathQueue);

	/*
	* Function to attack this enemy.
	* 
	* @return true if the enemy is killed, false otherwise.
	*/
	virtual bool AttackThis(int64 damage);

	//Removes the enemy from the world and gives it back to the WaveManager through the PlayerController
	virtual void RemoveThis();

	/*
	* Function to spawn this enemy.
	* Called by wave manager when the enemy is spawned.
	*/
	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void Spawn();

	double DistanceToNextNode() const;

	int64 GetQueueIndex() const;

	/*
	* An enemy is less than another enemu if they are closer to the end of the path.
	* 
	* This function assumes that every enemy has the same path.
	*/
	bool operator<(const AAbstractEnemy& other) const;

	void TeleportGlobal(FVector newLocation);

	void MoveToNextNode(float DeltaTime);

};
