// Fill out your copyright notice in the Description page of Project Settings.


#include "AbstractEnemy.h"

#include <TDPlayerController.h>

#include "Kismet/GameplayStatics.h"

// Sets default values
AAbstractEnemy::AAbstractEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	queueIndex = 0;
	isAlive = false;
	speed = 100;
	healthMax = 1;
	healthCurrent = healthMax;
	DamageDealt = 5;

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

void AAbstractEnemy::SetPathQueue(TDeque<TObjectPtr<AGraphNode>> PathQueue)
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
		RemoveThis();
	}
	return !isAlive;
}

void AAbstractEnemy::RemoveThis()
{
	if (TObjectPtr<ATDPlayerController> PlayerController = Cast<ATDPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
		PlayerController->AddDeadEnemyToWaveManager(this);
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Wrong PlayerController is being used"));
	}
	isAlive = false;
	pathQueue.Empty();
}

void AAbstractEnemy::Spawn()
{
	if (pathQueue.IsEmpty()) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("PathQueue is empty!"));
		return;
	}
	this->healthCurrent = this->healthMax;
	this->isAlive = true;
	this->queueIndex = 0;
	this->SetActorLocation(this->pathQueue[0]->GetActorLocation());
}

double AAbstractEnemy::DistanceToNextNode() const
{
	TObjectPtr<AGraphNode> nextNode = this->pathQueue[this->queueIndex];
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
	//if (this->queueIndex >= this->pathQueue.Num())
	//{
	//	return;
	//}

	//Checks if the queue is empty before using it, in order to avoid errors
	if (pathQueue.IsEmpty()) {

		TObjectPtr<ATDPlayerController> PlayerController = Cast<ATDPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		PlayerController->LoseHealth(DamageDealt);
		this->RemoveThis();
	}

	TObjectPtr<AGraphNode> nextNode = this->pathQueue.First();
	FVector direction = nextNode->GetActorLocation() - this->GetActorLocation();
	direction.Normalize();
	this->SetActorLocation(this->GetActorLocation() + direction * speed * DeltaTime);

	if (FVector::Dist(this->GetActorLocation(), nextNode->GetActorLocation()) < 1)
	{
		this->pathQueue.PopFirst();
	}

	//There is also a check if queue is empty here, one of these is redundant, however I have yet to find out which one
	if (pathQueue.IsEmpty())
	{
		TObjectPtr<ATDPlayerController> PlayerController = Cast<ATDPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		PlayerController->LoseHealth(DamageDealt);
		this->RemoveThis();
	}
}