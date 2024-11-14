// Fill out your copyright notice in the Description page of Project Settings.


#include "ValueNode.h"


ValueNode::ValueNode(TObjectPtr<AGraphNode>newState, FVector endCoordinates)
{
	State = newState;
	heuristic = endCoordinates.Dist(newState->GetActorLocation(),endCoordinates);
}

