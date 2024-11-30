// Fill out your copyright notice in the Description page of Project Settings.


#include "PathQueue.h"
#include <Logging/StructuredLog.h>

PathQueue::PathQueue()
{
	TArray<TObjectPtr<AGraphNode>> Path;
	Path.Init(nullptr, 1);
	PathPtr = MakeShared<TArray<TObjectPtr<AGraphNode>>>(Path);
	currentIndex = 1;
	original = true;
}

PathQueue::PathQueue(int size)
{
	TArray<TObjectPtr<AGraphNode>> Path;
	Path.Init(nullptr, size);
	PathPtr = MakeShared<TArray<TObjectPtr<AGraphNode>>>(Path);
	currentIndex = 0;
	original = true;
}

PathQueue::PathQueue(const PathQueue& other)
{
	PathPtr = other.PathPtr;
	currentIndex = other.currentIndex;
	original = false;
	UE_LOGFMT(LogTemp, Display, "Cloning Path");
}

TObjectPtr<AGraphNode> PathQueue::GetCurrentNode() const
{
	TArray<TObjectPtr<AGraphNode>> Path = *PathPtr;
	return Path[currentIndex];
}

bool PathQueue::Resize(int newSize)
{
	if (original == false) return false;
	UE_LOGFMT(LogTemp, Warning, "Path Resize");

	PathPtr->Empty();
	PathPtr->Init(nullptr, newSize);
	return true;
}

bool PathQueue::GoNextNode()
{
	if (RemainingNodes() <= 0)
	{
		currentIndex++;
		return true;
	}

	return false;
}

int PathQueue::RemainingNodes() const
{
	return PathPtr->Num() - currentIndex;
}

bool PathQueue::IsEmpty() const
{
	return RemainingNodes() <= 0;
}

void PathQueue::SetNode(TObjectPtr<AGraphNode> node, int index)
{
	TArray<TObjectPtr<AGraphNode>> Path = *PathPtr;
	Path[index] = node;
}
