// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <GraphNode.h>


/**
 * @author Paulius
 */
class PROGRAMMING3TD_API ValueNode
{
private:
	float heuristic;
	TObjectPtr<AGraphNode> State;


public:
	ValueNode(TObjectPtr<AGraphNode>newState, FVector endCoordinates);
	
	TObjectPtr<AGraphNode>GetState() const { return State; };
	
	bool operator<(const ValueNode& other) const
	{
		return GetValue() < other.GetValue();
	};
	
	float GetValue() const { return State->GetThreatLevel()+heuristic; };
};

