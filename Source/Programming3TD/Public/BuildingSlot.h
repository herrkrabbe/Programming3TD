// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "AbstractTower.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GraphNode.h"
#include "BuildingSlot.generated.h"

/*
* The BuildingSlot class represents a location the player can build towers on.
* The BuildingSlot is also a node or state on a graph, and can be told which
* other BuildingSlots are adjacent to it, so that A* pathfinding can be used.
* 
* Remember to give the BuildingSlot the End Node/State before telling it which
* other BuildingSlots are adjacent, so that it can calculate the heuristic value
* for the A* algorithm.
*/
UCLASS()
class PROGRAMMING3TD_API ABuildingSlot : public AGraphNode
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuildingSlot();

private:

	/*
	* Bool to check if the BuildingSlot has a building on it.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building", meta=(AllowPrivateAccess="true"))
	bool hasBuilding = false;


	/*
	* The BuildingSlot that is the end node for the A* algorithm.
	*/
	//UPROPERTY(BlueprintReadWrite, Category = "Graph", meta = (AllowPrivateAccess = "true"))
	//TObjectPtr<ABuildingSlot> EndNode;

	/*
	 *Tower
	 */

	/*
	 *Creating class based off AAbstractTower in order to spawn it
	 */
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building")
	TSubclassOf<AAbstractTower> TowerClass;

private:
	/*
	 *Reference to tower on BuildPlot in order to get the ThreatLevel used for the heuristic
	 */
	TObjectPtr<AAbstractTower> ChildTower = nullptr;

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/*
	* Can this BuildingSlot be built on?
	* @return True if the BuildingSlot is empty and can be built on.
	*/
	UFUNCTION(BlueprintCallable, Category = "Building")
	virtual bool CanBuild();

	/*
	* Build a building on this BuildingSlot.
	* 
	* @return True if the building was built successfully.
	*/
	UFUNCTION(BlueprintCallable, Category = "Building")
	virtual bool Build();

};
