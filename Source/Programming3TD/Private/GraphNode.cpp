// Fill out your copyright notice in the Description page of Project Settings.


#include "GraphNode.h"

// Sets default values
AGraphNode::AGraphNode()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGraphNode::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGraphNode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

double AGraphNode::GetValue(AGraphNode* endNode)
{
	return GetThreatLevel() + FVector::Dist(this->GetActorLocation(), endNode->GetActorLocation());;
}

double AGraphNode::GetThreatLevel() const
{
	return ThreatLevel;
}


bool AGraphNode::isAdjacent(AGraphNode* otherBuildingSlot)
{
	if (AdjacentMap.Contains(otherBuildingSlot))
	{
		return true;
	}
	return false;
}

void AGraphNode::AddAdjacent(AGraphNode* otherBuildingSlot)
{
	if (isAdjacent(otherBuildingSlot))
	{
		return;
	}
	if (otherBuildingSlot == this) {
		return;
	}

	AdjacentMap.Add(otherBuildingSlot, otherBuildingSlot);
	ArrayOfAdjacencyMap.Add(otherBuildingSlot);

	otherBuildingSlot->AddAdjacent(this); //this line is after to prevent an infinite loop
}

TArray<AGraphNode*> AGraphNode::GetAdjacent()
{
	return ArrayOfAdjacencyMap;
}
