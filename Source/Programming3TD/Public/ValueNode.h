// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <GraphNode.h>
#include "UObject/NoExportTypes.h"
#include "ValueNode.generated.h"

/*
 * @author Paulius
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
	UValueNode(TObjectPtr<AGraphNode>newState, FVector endCoordinates);
	
	TObjectPtr<AGraphNode>GetState() const { return State; };

	bool operator<(const UValueNode& other) const
	{
		if (State == nullptr) { throw("ValueNode was compared while state was nullpointer"); }
		if (other.GetState() == nullptr) { throw("Other ValueNode was compared while state was nullpointer"); }
		return GetValue() < other.GetValue();
	};
	
	/* Getcost of graphnode + heuristic, does not include cost from parent to 
	* @return GetThreatlevel+heuristic(valuenode)
	*/
	float GetValue() const { return State->GetThreatLevel() + heuristic; };

private:
	float heuristic;
	TObjectPtr<AGraphNode> State;

};

