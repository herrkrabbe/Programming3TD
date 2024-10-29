// Fill out your copyright notice in the Description page of Project Settings.


#include "AbstractEnemy.h"

// Sets default values
AAbstractEnemy::AAbstractEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	queueIndex = 0;
	isAlive = 0;
	speed = 100;
	healthMax = 1;
	healthCurrent = healthMax;

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

	if (isAlive)
	{
		MoveToNextNode(DeltaTime);
	}

}

void AAbstractEnemy::SetPathQueue(TDeque<TObjectPtr<ABuildingSlot>> PathQueue)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Setting pathqueue"));
	this->pathQueue = PathQueue;
	if (pathQueue.IsEmpty()) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Failed to set PathQueue"));

	}
}

bool AAbstractEnemy::AttackThis(int64 damage)
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
	if (pathQueue.IsEmpty()) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("PathQueue is empty!"));
		return;
	}
	this->healthCurrent = this->healthMax;
	this->isAlive = 1;
	this->queueIndex = 0;
	this->SetActorLocation(this->pathQueue[0]->GetActorLocation());
}

double AAbstractEnemy::DistanceToNextNode() const
{
	TObjectPtr<ABuildingSlot> nextNode = this->pathQueue[this->queueIndex];
	return FVector::Dist(this->GetActorLocation(), nextNode->GetActorLocation());
}

int64 AAbstractEnemy::GetQueueIndex() const
{
	return queueIndex;
}

bool AAbstractEnemy::operator<(const AAbstractEnemy& other) const
{
	if (this->queueIndex > other.queueIndex)
		return true;

	if (DistanceToNextNode() > other.DistanceToNextNode())
		return true;

	return false;
}

void AAbstractEnemy::TeleportGlobal(FVector newLocation)
{
	this->SetActorLocation(newLocation);
}

void AAbstractEnemy::MoveToNextNode(float DeltaTime)
{
	if (this->queueIndex >= this->pathQueue.Num())
	{
		return;
	}

	TObjectPtr<ABuildingSlot> nextNode = this->pathQueue[this->queueIndex];
	FVector direction = nextNode->GetActorLocation() - this->GetActorLocation();
	direction.Normalize();
	this->SetActorLocation(this->GetActorLocation() + direction * speed * DeltaTime);

	if (FVector::Dist(this->GetActorLocation(), nextNode->GetActorLocation()) < 1)
	{
		this->queueIndex++;
	}
}