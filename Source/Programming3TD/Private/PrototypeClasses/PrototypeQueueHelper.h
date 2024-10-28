// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Containers/Deque.h"
#include <BuildingSlot.h>

#include <AbstractEnemy.h>
#include "PrototypeQueueHelper.generated.h"
UCLASS()
class APrototypeQueueHelper : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APrototypeQueueHelper();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	TDeque<TObjectPtr<ABuildingSlot>> queue;

	UFUNCTION(BlueprintCallable)
	void AddToQueue(ABuildingSlot* slot);

	UFUNCTION(BlueprintCallable)
	void SetEnemyQueue(AAbstractEnemy* enemy);
};
