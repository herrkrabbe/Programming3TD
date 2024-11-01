// Fill out your copyright notice in the Description page of Project Settings.


#include "AStar.h"

TDeque<TObjectPtr<AGraphNode>> AStar::FindPath(TObjectPtr<AGraphNode> start, TObjectPtr<AGraphNode> end)
{
	TDeque<TObjectPtr<AGraphNode>> Path;

	// PriorityQueue using BinaryHeap implementation
	// Stores the nodes that are open to be evaluated
	TArray<TObjectPtr<SearchNode>> OpenQueue;

	int identity = 0;
	SearchNode startNode(start, end, identity);
	OpenQueue.HeapPush(startNode);
	identity++;

	// Stores the states that have already been evaluated
	TMap<TObjectPtr<AGraphNode>, float> CostMap;
	CostMap.Add(startNode.GetState(), startNode.GetCost());

	// Stores the total weight of a state
	TMap<TObjectPtr<AGraphNode>, float> WeightMap;
	WeightMap.Add(startNode.GetState(), startNode.GetExpectedCost());

	TObjectPtr<SearchNode> CurrentNode = nullptr;


	while (!OpenQueue.IsEmpty()) {
		OpenQueue.HeapPop(CurrentNode); // Gets the top item in the open queue. O(log q) where q is number of items in the queue

		if (CurrentNode->GetState() == end) { // target is found. Get path to end, and break the loop to return the path
			Path = CurrentNode->GetPath();
			break;
		}

		TArray<TObjectPtr<AGraphNode>> AdjacentNodes;
		AdjacentNodes = CurrentNode->GetState()->GetAdjacent();


		for (TObjectPtr<AGraphNode> neighbour : AdjacentNodes) {
			SearchNode neighbourNode(neighbour, end, identity, CurrentNode);
			identity++;

			if (!CostMap.Contains(neighbour) || neighbourNode.GetCost() < CostMap[neighbour]) { //the right side of OR statement only triggers if the map already contains the node
				CostMap.Add(neighbour, neighbourNode.GetCost());
				WeightMap.Add(neighbour, neighbourNode.GetExpectedCost());
				OpenQueue.HeapPush(neighbourNode);
			}
		}


		AdjacentNodes.Empty();

	}

	return Path;
}
