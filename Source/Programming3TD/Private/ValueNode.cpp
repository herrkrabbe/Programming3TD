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

void UValueNode::Initialize(TObjectPtr<AGraphNode> newState, FVector endCoordinates, float extraCost)
{
	State = newState;
	heuristic = endCoordinates.Dist(newState->GetActorLocation(), endCoordinates);
	SetExtraCost(extraCost);
}

void UValueNode::SetExtraCost(float extraCost)
{
	cost = State->GetThreatLevel() + extraCost;
}
