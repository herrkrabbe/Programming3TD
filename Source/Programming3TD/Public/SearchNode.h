// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <GraphNode.h>
#include "Containers/Deque.h"

/**
 * 
 */
class PROGRAMMING3TD_API SearchNode
{
private: //variables
	TObjectPtr<SearchNode> Parent;
	TObjectPtr<AGraphNode> State;
	int64 Identity;
	float Heuristic;
	float Cost;
	int64 Depth;

public: //functions
	SearchNode(TObjectPtr<AGraphNode> state, TObjectPtr<AGraphNode> endNode, int64 ID, TObjectPtr<SearchNode> parent = nullptr);

	void SetEndNode(TObjectPtr<AGraphNode> endNode);

	float GetCost() const;

	/*
	* Gets the expected cost of the node, which is the cost + the distance to the end node.
	*/
	float GetExpectedCost() const;

	TObjectPtr<SearchNode> GetParent() const { return Parent; }

	TObjectPtr<AGraphNode> GetState() const { return State; }

	TDeque<TObjectPtr<AGraphNode>> GetPath() const;

	bool operator<(const SearchNode& other) const
	{
		return GetExpectedCost() < other.GetExpectedCost();
	}


private: //functions

	void MakePath(TDeque<TObjectPtr<AGraphNode>> &path) const;
};
