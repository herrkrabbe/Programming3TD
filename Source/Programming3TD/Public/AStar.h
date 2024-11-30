// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <ValueNode.h>
#include <SearchNode.h>
#include "Containers/Deque.h"
#include "PathQueue.h"

/**
 * 
 */
class PROGRAMMING3TD_API AStar
{
public:
	/*
	* Function to find a path between two nodes.
	* 
	* @param startNode The node to start the search from
	* @param endNode The node to search for
	* @return A deque containing the path from start to end. Deque is empty if no path was found.
	*/
	static TDeque<TObjectPtr<AGraphNode>> FindPath(TObjectPtr<AGraphNode> startNode, TObjectPtr<AGraphNode> endNode);

	/*
	* Function to find a path between two nodes. The function uses a map to store parents.
	* 
	* @param startNode The node to start the search from
	* @param endNode The node to search for
	* @return A deque containing the path from start to end. Deque is empty if no path was found.

	*/
	static PathQueue FindPathMapImplementation(TObjectPtr<AGraphNode> startNode, TObjectPtr<AGraphNode> endNode);
};
