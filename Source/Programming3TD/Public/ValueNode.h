// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <GraphNode.h>
#include "UObject/NoExportTypes.h"
#include "ValueNode.generated.h"

/*
* ValueNode is an intermediate class between A* and a GraphNode.
* 
* ValueNode is used to store the heuristic of a node used in A*, which a GraphNode does not have.
* The ValueNode is also sortable using the < operator.
* 
* Remember to call the Initialize function after creating this object.
* 
* 
 * @author Paulius
 * @author Alexander
 */
UCLASS()
class PROGRAMMING3TD_API UValueNode : public UObject
{
	GENERATED_BODY()

public:
	UValueNode();
	/*
	* newState is collecting the state of AGraphNode, transforming it to a new float for ValueNode.
	* endCoordinates are the *new* heuristic values based on FVector:Dist("euclidean") 2 values, newStates location, and endCoordinates.
	*/
	UValueNode(TObjectPtr<AGraphNode>newState, FVector endCoordinates, float extraCost = 0.0f);

	/*
	* Initialises the field variables of the ValueNode.
	* 
	* @param newState is the GraphNode the ValueNode represents.
	* @param endCoordinates are the coordinates of the end node of the path.
	*/
	void Initialize(TObjectPtr<AGraphNode>newState, FVector endCoordinates, float extraCost = 0.0f, int32 depth = 0);
	
	TObjectPtr<AGraphNode>GetState() const { return State; };

	bool operator<(const UValueNode& other) const
	{
		if (State == nullptr) { throw("ValueNode was compared while state was nullpointer"); }
		if (other.GetState() == nullptr) { throw("Other ValueNode was compared while state was nullpointer"); }
		return GetValue() < other.GetValue();
	};
	
	/* Getcost of graphnode + heuristic + extraCost, where extra cost should be the extra cost from the parent. 
	* @return cost+heuristic(valuenode)
	*/
	float GetValue() const { return cost + heuristic; };

	/*
	* Get the cost of the node.
	* @return cost from state + extra cost
	*/
	float GetCost() const { return cost; };

	/*
	* Get the heuristic of the node.
	* @return heuristic
	*/
	float GetHeuristic() const { return heuristic; };

	/*
	* Set the extra cost of the node. Should be called only when parent changes.
	* @param extraCost is the cost of the parent node
	*/
	void SetExtraCost(float extraCost);

	int32 GetDepth() const;

private:
	float heuristic;
	float cost;
	TObjectPtr<AGraphNode> State;
	int32 Depth;

};

