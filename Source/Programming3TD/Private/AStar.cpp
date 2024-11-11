// Fill out your copyright notice in the Description page of Project Settings.


#include "AStar.h"
#include <Logging/StructuredLog.h>

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





	while (!OpenQueue.IsEmpty()) {
		TObjectPtr<SearchNode> CurrentNode = OpenQueue.HeapTop();
		OpenQueue.HeapPopDiscard(); // Gets the top item in the open queue. O(log q) where q is number of items in the queue

		if (CurrentNode->GetState() == end) { // target is found. Get path to end, and break the loop to return the path
			for (auto e : CostMap) {
				UE_LOGFMT(LogTemp, Warning, "Key: `{0}`, Cost: `{1}`", *e.Key->GetName(), e.Value);
			}
			Path = CurrentNode->GetPath();
			break;
		}

		TArray<TObjectPtr<AGraphNode>> AdjacentNodes;
		AdjacentNodes = CurrentNode->GetState()->GetAdjacent();


		for (TObjectPtr<AGraphNode> neighbour : AdjacentNodes) {
			if (neighbour == CurrentNode->GetState()) {
				UE_LOGFMT(LogTemp, Warning, "Neighbour is self. Skip");
				continue; //skip if the neighbour is self
			}
			else {
				UE_LOGFMT(LogTemp, Warning, "Current: {0}, Neighbour: {1}", CurrentNode->GetState()->GetName(), neighbour->GetName());
			}
			SearchNode neighbourNode(neighbour, end, identity, CurrentNode);
			identity++;

			if (!CostMap.Contains(neighbour) || neighbourNode.GetCost() < CostMap[neighbour]) { //the right side of OR statement only triggers if the map already contains the node
				CostMap.Add(neighbour, neighbourNode.GetCost());
				OpenQueue.HeapPush(neighbourNode);
			}
		}


		AdjacentNodes.Empty();

	}

	return Path;
}

TDeque<TObjectPtr<AGraphNode>> AStar::FindPathMapImplementation(TObjectPtr<AGraphNode> start, TObjectPtr<AGraphNode> end)
{
	TDeque<TObjectPtr<AGraphNode>> Path;

	// PriorityQueue using BinaryHeap implementation
	// Stores the nodes that are open to be evaluated
	TArray<TObjectPtr<AGraphNode>> OpenQueue;

	OpenQueue.HeapPush(start);

	// Stores the states that have already been evaluated
	TMap<TObjectPtr<AGraphNode>, float> CostMap;
	CostMap.Add(start, start->GetThreatLevel());

	// Stores the parent of each node
	TMap<TObjectPtr<AGraphNode>, TObjectPtr<AGraphNode>> ParentMap;
	ParentMap.Add(start, nullptr);

	while (!OpenQueue.IsEmpty()) {
		TObjectPtr<AGraphNode> CurrentNode = OpenQueue.HeapTop();
		OpenQueue.HeapPopDiscard(); // Gets the top item in the open queue. O(log v) where v is number of items in the queue

		if (CurrentNode == end) { // target is found. Get path to end, and break the loop to return the path
			TObjectPtr<AGraphNode> Current = CurrentNode;
			while (Current != nullptr) {
				Path.PushFirst(Current);
				Current = ParentMap[Current];
			}
			break;
		}
		
		TArray<TObjectPtr<AGraphNode>> AdjacentNodes;
		AdjacentNodes = CurrentNode->GetAdjacent();

		for (TObjectPtr<AGraphNode> neighbour : AdjacentNodes) {
			if (neighbour == CurrentNode) {
				continue; //skip if the neighbour is self
			}

			float newCost = CostMap[CurrentNode] + neighbour->GetThreatLevel();
			if (!CostMap.Contains(neighbour) || newCost < CostMap[neighbour]) { //the right side of OR statement only triggers if the map already contains the node
				CostMap.Add(neighbour, newCost);
				OpenQueue.HeapPush(neighbour);
				ParentMap.Add(neighbour, CurrentNode);
			}
		}
	}

	return Path;
}
