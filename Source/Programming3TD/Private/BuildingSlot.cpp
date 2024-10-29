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
	
}

// Called every frame
void ABuildingSlot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

double ABuildingSlot::GetValue(ABuildingSlot* endNode)
{
	return ThreatLevel + FVector::Dist(this->GetActorLocation(), endNode->GetActorLocation());;
}



bool ABuildingSlot::CanBuild()
{	//If there is no building, returns true
	return !hasBuilding;
}

bool ABuildingSlot::Build()
{
	//Only builds if there is no building already on the building slot
	if (CanBuild())
	{
		ChildTower = GetWorld()->SpawnActor<AAbstractTower>(TowerClass, GetActorLocation(), GetActorRotation());
		hasBuilding = true;
		ThreatLevel += ChildTower->ThreatLevel;

		return ChildTower;
	}
	return false;
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

