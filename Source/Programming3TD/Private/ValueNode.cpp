// Fill out your copyright notice in the Description page of Project Settings.


#include "ValueNode.h"


UValueNode::UValueNode()
{
	heuristic = 0;
	State = nullptr;
}

UValueNode::UValueNode(TObjectPtr<AGraphNode>newState, FVector endCoordinates)
{
	State = newState;
	heuristic = endCoordinates.Dist(newState->GetActorLocation(),endCoordinates);
}