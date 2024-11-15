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
	TArray <TObjectPtr< UValueNode >> OpenQueue;

	//Create initial node
	FVector endCoordinates = end->GetActorLocation();
	TObjectPtr<UValueNode> startValueNode = NewObject<UValueNode>();
	startValueNode->Initialize(start, endCoordinates);

	OpenQueue.HeapPush(*startValueNode);

	// Stores the states that have already been evaluated
	TMap<TObjectPtr<AGraphNode>, float> CostMap;
	CostMap.Add(start, start->GetThreatLevel());

	// Stores the parent of each node
	TMap<TObjectPtr<UValueNode>, TObjectPtr<UValueNode>> ParentMap;
	ParentMap.Add(startValueNode, nullptr);

	while (!OpenQueue.IsEmpty()) {
		TObjectPtr<UValueNode> CurrentNode = OpenQueue.HeapTop();
		OpenQueue.HeapPopDiscard(); // Gets the top item in the open queue. O(log v) where v is number of items in the queue

		if (CurrentNode->GetState() == end) { // target is found. Get path to end, and break the loop to return the path
			TObjectPtr<UValueNode> Current = CurrentNode;
			while (Current != nullptr) {
				Path.PushFirst(Current->GetState());
				Current = ParentMap[Current];
			}
			OpenQueue.Empty();
			break;
		}
		
		TArray<TObjectPtr<AGraphNode>> AdjacentNodes;
		AdjacentNodes = CurrentNode->GetState()->GetAdjacent();

		for (TObjectPtr<AGraphNode> neighbour : AdjacentNodes) {
			if (neighbour == CurrentNode->GetState()) {
				continue; //skip if the neighbour is self
			}

			float newCost = CostMap[CurrentNode->GetState()] + neighbour->GetThreatLevel() + FVector::Distance(neighbour->GetActorLocation(), CurrentNode->GetState()->GetActorLocation());
			if (!CostMap.Contains(neighbour) || newCost < CostMap[neighbour]) { //the right side of OR statement only triggers if the map already contains the node
				TObjectPtr<UValueNode> neighbourValueNode = NewObject<UValueNode>();
				neighbourValueNode->Initialize(neighbour, endCoordinates);
				
				CostMap.Add(neighbour, newCost);
				OpenQueue.HeapPush(*neighbourValueNode);
				ParentMap.Add(neighbourValueNode, CurrentNode);
				GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Red, FString::Printf(TEXT("Node: %s, Value: %f, Heuristic: %f, Cost: %f"), *neighbour->GetName(), neighbourValueNode->GetValue(), (neighbourValueNode->GetValue()-CostMap[neighbour]), CostMap[neighbour]));
			}
		}
	}

	return Path;
}
