// Fill out your copyright notice in the Description page of Project Settings.


#include "ValueNode.h"


UValueNode::UValueNode()
{
	heuristic = 0;
	State = nullptr;
}

UValueNode::UValueNode(TObjectPtr<AGraphNode>newState, FVector endCoordinates, float extraCost)
{
	Initialize(newState, endCoordinates, extraCost);
}

void UValueNode::Initialize(TObjectPtr<AGraphNode> newState, FVector endCoordinates, float extraCost, int32 depth)
{
	State = newState;
	heuristic = endCoordinates.Dist(newState->GetActorLocation(), endCoordinates);
	SetExtraCost(extraCost);
	Depth = depth;
}

void UValueNode::SetExtraCost(float extraCost)
{
	cost = State->GetThreatLevel() + extraCost;
}

int32 UValueNode::GetDepth() const
{
	return Depth;
}
