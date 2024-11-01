// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <SearchNode.h>
#include "Containers/Deque.h"

/**
 * 
 */
class PROGRAMMING3TD_API AStar
{
public:
	static TDeque<TObjectPtr<AGraphNode>> FindPath(TObjectPtr<AGraphNode> startNode, TObjectPtr<AGraphNode> endNode);
};
