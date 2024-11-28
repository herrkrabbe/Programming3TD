// Fill out your copyright notice in the Description page of Project Settings.


#include "PathQueue.h"

UPathQueue::UPathQueue()
{
}

//UPathQueue::UPathQueue(int32 size)
//{
//	TArray<TObjectPtr<AGraphNode>> constructorArray;
//	constructorArray.Init(nullptr, size);
//	PathArray = constructorArray;
//	CurrentIndex = 0;
//}
//
//UPathQueue::UPathQueue(const UPathQueue& original)
//{
//	PathArray = original.PathArray;
//	CurrentIndex = original.CurrentIndex;
//}

void UPathQueue::Set(TObjectPtr<AGraphNode> inserted, int32 insertIndex)
{
	PathArray->Insert(inserted, insertIndex);
}

TObjectPtr<AGraphNode> UPathQueue::GetCurrentNode()
{
	TArray<TObjectPtr<AGraphNode>> nodeArray = *PathArray;
	return nodeArray[CurrentIndex];
}

void UPathQueue::GoNext()
{
	CurrentIndex++;
}

TObjectPtr<UPathQueue> UPathQueue::CreatePathQueue(int32 size)
{
	UPathQueue* newPathQueue = NewObject<UPathQueue>();

	TArray<TObjectPtr<AGraphNode>> constructorArray;
	constructorArray.Init(nullptr, size);
	newPathQueue->PathArray = &constructorArray;
	newPathQueue->CurrentIndex = 0;
	return newPathQueue;
}

TObjectPtr<UPathQueue> UPathQueue::CreatePathQueue(const UPathQueue& original)
{
	UPathQueue* newPathQueue = NewObject<UPathQueue>();

	newPathQueue->PathArray = original.PathArray;
	newPathQueue->CurrentIndex = original.CurrentIndex;
	return newPathQueue;
}
