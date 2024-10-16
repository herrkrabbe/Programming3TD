// Fill out your copyright notice in the Description page of Project Settings.


#include "AbstractEnemy.h"

// Sets default values
AAbstractEnemy::AAbstractEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAbstractEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAbstractEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAbstractEnemy::SetPathQueue(TArray<TObjectPtr<ABuildingSlot>> PathQueue)
{
	this->pathQueue = PathQueue;
}

bool AAbstractEnemy::AttackThis(int32 damage)
{
	this->healthCurrent -= damage;
	if (this->healthCurrent <= 0)
	{
		isAlive = 0;
	}
	return !isAlive;
}

void AAbstractEnemy::Spawn()
{
	if (pathQueue.IsEmpty()) return;

	this->healthCurrent = this->healthMax;
	this->isAlive = 1;
	this->queueIndex = 0;
	this->SetActorLocation(this->pathQueue[0]->GetActorLocation());
}

