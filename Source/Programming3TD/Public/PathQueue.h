// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <GraphNode.h>

/**
 * 
 */
class PROGRAMMING3TD_API PathQueue
{
public:
	PathQueue();
	PathQueue(int size);
	PathQueue(const PathQueue& other);

	TObjectPtr<AGraphNode> GetCurrentNode() const;

	bool Resize(int newSize);

	bool GoNextNode();

	int RemainingNodes() const;

	bool IsEmpty() const;

	void SetNode(TObjectPtr<AGraphNode> node, int index);

private:
	TSharedPtr<TArray<TObjectPtr<AGraphNode>>> PathPtr;
	int currentIndex;
	bool original;
};
