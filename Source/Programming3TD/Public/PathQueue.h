// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GraphNode.h"
#include "UObject/NoExportTypes.h"
#include "PathQueue.generated.h"

/**
 * 
 */
UCLASS()
class PROGRAMMING3TD_API UPathQueue : public UObject
{
	GENERATED_BODY()
public:
	UPathQueue();

	//UPathQueue(int32 size);

	//UPathQueue(const UPathQueue& original);

	void Set(TObjectPtr<AGraphNode> inserted, int32 insertIndex);
	
	TObjectPtr<AGraphNode> GetCurrentNode();

	void GoNext();

	static TObjectPtr<UPathQueue> CreatePathQueue(int32 size);

	static TObjectPtr<UPathQueue> CreatePathQueue(const UPathQueue& original);
private:
	TArray<TObjectPtr<AGraphNode>>* PathArray;
	int32 CurrentIndex;
};
