// Fill out your copyright notice in the Description page of Project Settings.


#include "PrototypeClasses/PrototypeQueueHelper.h"

// Sets default values
APrototypeQueueHelper::APrototypeQueueHelper()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APrototypeQueueHelper::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APrototypeQueueHelper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APrototypeQueueHelper::AddToQueue(AGraphNode* slot)
{
	queue.PushLast(slot);
}

void APrototypeQueueHelper::SetEnemyQueue(AAbstractEnemy* enemy)
{
	enemy->SetPathQueue(queue);
}

