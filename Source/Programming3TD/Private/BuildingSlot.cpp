// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingSlot.h"

// Sets default values
ABuildingSlot::ABuildingSlot()
{
 	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AddAdjacent(this);

	

}

// Called when the game starts or when spawned
void ABuildingSlot::BeginPlay()
{
	Super::BeginPlay();

	SetEndNode(this);
	
}

// Called every frame
void ABuildingSlot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

double ABuildingSlot::GetValue()
{
	return ThreatLevel + DistanceToEnd;
}

void ABuildingSlot::SetEndNode(ABuildingSlot* newEndNode)
{
	this->EndNode = newEndNode;
	DistanceToEnd = FVector::Dist(this->GetActorLocation(), newEndNode->GetActorLocation());
}

ABuildingSlot* ABuildingSlot::GetEndNode()
{
	return EndNode;
}


bool ABuildingSlot::CanBuild()
{
	return hasBuilding;
}

bool ABuildingSlot::Build()
{
	return false; //TODO
}

bool ABuildingSlot::isAdjacent(ABuildingSlot* otherBuildingSlot)
{
	if (AdjacentMap.Contains(otherBuildingSlot))
	{
		return true;
	}
	return false;
}

void ABuildingSlot::AddAdjacent(ABuildingSlot* otherBuildingSlot)
{
	if (isAdjacent(otherBuildingSlot))
	{
		return;
	}

	AdjacentMap.Add(otherBuildingSlot, otherBuildingSlot);
	ArrayOfAdjacencyMap.Add(otherBuildingSlot);

	otherBuildingSlot->AddAdjacent(this); //this line is after to prevent an infinite loop
}

TArray<ABuildingSlot*> ABuildingSlot::GetAdjacent()
{
	return ArrayOfAdjacencyMap;
}

