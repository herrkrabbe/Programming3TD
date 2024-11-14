// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingSlot.h"

// Sets default values
ABuildingSlot::ABuildingSlot() : AGraphNode()
{

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



bool ABuildingSlot::CanBuild()
{	//If there is no building, returns false
	return hasBuilding;
}

bool ABuildingSlot::Build()
{
	//Only builds if there is no building already on the building slot
	if (CanBuild())
		return false;

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	ChildTower = GetWorld()->SpawnActor<AAbstractTower>(TowerClass, GetActorLocation(), GetActorRotation(), SpawnParams);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Tower built"));
	hasBuilding = true;
	if (ChildTower)
	{
		ThreatLevel = ThreatLevel + ChildTower->ThreatLevel;
	}
	else return false;

	return true;

}

