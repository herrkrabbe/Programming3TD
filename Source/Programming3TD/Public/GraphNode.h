// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GraphNode.generated.h"

UCLASS()
class PROGRAMMING3TD_API AGraphNode : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGraphNode();

protected:
	/*
	* ThreatLevel is the additional cost of this node. Buildings affect the BuildingSlot's ThreatLevel.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Graph", meta = (AllowPrivateAccess = "true"))
	double ThreatLevel = 0;

private:
	/*
	* A Map storing which BuildingSlots are adjacent to this BuildingSlot.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Graph", meta = (AllowPrivateAccess = "true"))
	TMap<TObjectPtr<AGraphNode>, TObjectPtr<AGraphNode>> AdjacentMap;

	/*
	* Auxiliary array to AdjacencyMap. When a new BuildingSlot is added to the AdjacencyMap, it is also added to this array.
	* This way, GetAdjacencent happens on time O(1) instead of an uncertain Big O.
	*/
	TArray<AGraphNode*> ArrayOfAdjacencyMap;

	/*
	* The BuildingSlot that is the end node for the A* algorithm.
	*/
	//UPROPERTY(BlueprintReadWrite, Category = "Graph", meta = (AllowPrivateAccess = "true"))
	//TObjectPtr<AGraphNode> EndNode;
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
	virtual double GetValue(AGraphNode* endNode);

	virtual double GetThreatLevel() const;


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
	virtual bool isAdjacent(AGraphNode* otherBuildingSlot);

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
	virtual void AddAdjacent(AGraphNode* otherBuildingSlot);


	/*
	* Get all adjacent building slots, with self as first element.
	*
	* Time complexity: O(1)
	*
	* @return An array of pointers to all adjacent BuildingSlots.
	*/
	UFUNCTION(BlueprintCallable, Category = "Graph")
	virtual TArray<AGraphNode*> GetAdjacent();


};
