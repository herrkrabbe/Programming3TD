// Fill out your copyright notice in the Description page of Project Settings.


#include "SearchNode.h"

SearchNode::SearchNode(TObjectPtr<AGraphNode> state, TObjectPtr<AGraphNode> endNode, int64 ID, TObjectPtr<SearchNode> parent)
{
	State = state;
	Parent = parent;
	SetEndNode(endNode);
	
	if (parent = nullptr)
	{
		Depth = 0;
		Cost = state->GetThreatLevel();
	}
	else
	{
		Depth = parent->Depth + 1;

		float ParentCost = Parent->GetCost();
		float DistanceCost = FVector::Dist(State->GetActorLocation(), Parent->State->GetActorLocation());
		float ThreatLevelCost = State->GetThreatLevel();
		Cost = ParentCost + DistanceCost + ThreatLevelCost;
	}
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

TDeque<TObjectPtr<AGraphNode>> SearchNode::GetPath() const
{
	TDeque<TObjectPtr<AGraphNode>> path;
	path.PushLast(State);

	if (Depth != 0)
	{
		Parent->MakePath(path);
	}

	return path;
}

void SearchNode::MakePath(TDeque<TObjectPtr<AGraphNode>> &path) const
{
	path.PushFirst(State);

	if (Depth == 0)
	{
		return;
	}

	Parent->MakePath(path);
}

