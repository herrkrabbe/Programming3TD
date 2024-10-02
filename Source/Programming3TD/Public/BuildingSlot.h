// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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
class PROGRAMMING3TD_API ABuildingSlot : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuildingSlot();

private:
	/*
	* DistanceToEnd is an underestimated estimation of the cost to reach the end node.
	* It is used together with the ThreatLevel to determine the weighting (Value) of this node
	*/
	UPROPERTY(BlueprintReadWrite, Category="Graph", meta = (AllowPrivateAccess = "true"))
	double DistanceToEnd = 0;

	/*
	* ThreatLevel is the additional cost of this node. Buildings affect the BuildingSlot's ThreatLevel.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Graph", meta = (AllowPrivateAccess = "true"))
	double ThreatLevel = 0;

	/*
	* Bool to check if the BuildingSlot has a building on it.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building", meta=(AllowPrivateAccess="true"))
	bool hasBuilding = 0;

	/*
	* A Map storing which BuildingSlots are adjacent to this BuildingSlot.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Graph", meta = (AllowPrivateAccess = "true"))
	TMap<TObjectPtr<ABuildingSlot>, TObjectPtr<ABuildingSlot>> AdjacentMap;

	/*
	* Auxiliary array to AdjacencyMap. When a new BuildingSlot is added to the AdjacencyMap, it is also added to this array.
	* This way, GetAdjacencent happens on time O(1) instead of an uncertain Big O.
	*/
	TArray<ABuildingSlot*> ArrayOfAdjacencyMap;

	/*
	* The BuildingSlot that is the end node for the A* algorithm.
	*/
	UPROPERTY(BlueprintReadWrite, Category = "Graph", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ABuildingSlot> EndNode;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/*
	* Get the value (weight) of the BuildingSlot.
	* @return ThreatLevel + DistanceToEnd
	*/
	UFUNCTION(BlueprintCallable, Category = "Graph")
	virtual double GetValue();

	/*
	* Set the EndNode variable, and calculate the DistanceToEnd value.
	*/
	UFUNCTION(BlueprintCallable, Category = "Graph")
	virtual void SetEndNode(ABuildingSlot* newEndNode);

	/*
	* Get the end node
	* @return Pointer to the end node BuildingSlot
	*/
	UFUNCTION(BlueprintCallable, Category = "Graph")
	virtual ABuildingSlot* GetEndNode();

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

	/*
	* Checks if the other BuildingSlot is adjacent to this BuildingSlot.
	* 
	* Checks if this instance's AdjacentMap contains the other BuildingSlot as a key.
	* 
	* Time complexity: O(1)
	* 
	* @param otherBuildingSlot The BuildingSlot to check adjacency with.
	* @return True if the other BuildingSlot is adjacent to this BuildingSlot.
	*/
	UFUNCTION(BlueprintCallable, Category = "Graph")
	virtual bool isAdjacent(ABuildingSlot* otherBuildingSlot);

	/*
	* Add an adjacent BuildingSlot to this BuildingSlot.
	* 
	* Only adds the other BuildingSlot if it is not already adjacent.
	* 
	* Time complexity: O(1)
	* 
	* @param otherBuildingSlot The BuildingSlot to add as adjacent.
	*/
	UFUNCTION(BlueprintCallable, Category = "Graph")
	virtual void AddAdjacent(ABuildingSlot* otherBuildingSlot);


	/*
	* Get all adjacent building slots, with self as first element.
	* 
	* Time complexity: O(1)
	* 
	* @return An array of pointers to all adjacent BuildingSlots.
	*/
	UFUNCTION(BlueprintCallable, Category = "Graph")
	virtual TArray<ABuildingSlot*> GetAdjacent();

};
