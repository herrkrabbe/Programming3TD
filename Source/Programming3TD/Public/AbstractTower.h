// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbstractEnemy.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "AbstractTower.generated.h"

UCLASS()
class PROGRAMMING3TD_API AAbstractTower : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAbstractTower();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	int32 AttackDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	int32 AttackSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	USphereComponent* AttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	int32 ThreatLevel;

	//A linked list for enemies also needs to be defined, however TList does not appear to do what we need from my understanding of it


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
