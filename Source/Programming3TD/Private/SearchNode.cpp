// Fill out your copyright notice in the Description page of Project Settings.


#include "SearchNode.h"
#include <Logging/StructuredLog.h>

SearchNode::SearchNode(TObjectPtr<AGraphNode> state, TObjectPtr<AGraphNode> endNode, int64 ID, TObjectPtr<SearchNode> parent) // parent is nullptr in .h file
{

	State = state;

	Parent = parent;


	Identity = ID;
	SetEndNode(endNode);
	
	
	if (Parent == nullptr)
	{
		throw;
	}
	else
	{
		float ParentCost = Parent->GetCost();
		float DistanceCost = FVector::Dist(State->GetActorLocation(), Parent->State->GetActorLocation());
		float ThreatLevelCost = State->GetThreatLevel();
		Cost = ParentCost + DistanceCost + ThreatLevelCost;
	}

}

SearchNode::SearchNode(TObjectPtr<AGraphNode> state, TObjectPtr<AGraphNode> endNode, int64 ID)
{

	State = state;

	Parent = nullptr;

	Identity = ID;
	SetEndNode(endNode);

	Cost = state->GetThreatLevel();

}

void SearchNode::SetEndNode(TObjectPtr<AGraphNode> endNode)
{
	Heuristic = FVector::Dist(State->GetActorLocation(), endNode->GetActorLocation());
}

float SearchNode::GetCost() const
{
	return Cost;
}

float SearchNode::GetExpectedCost() const
{
	return GetCost() + Heuristic;
}

TDeque<TObjectPtr<AGraphNode>> SearchNode::GetPath()
{
	TDeque<TObjectPtr<AGraphNode>> path;
	path.PushLast(State);

	if (Parent != nullptr)
	{
		Parent->MakePath(path);
	}

	return path;
}

void SearchNode::MakePath(TDeque<TObjectPtr<AGraphNode>> &path)
{
	path.PushFirst(State);

	if (Parent == nullptr)
	{
		return;
	}
	Parent->MakePath(path);
}

