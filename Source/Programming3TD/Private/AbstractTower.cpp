// Fill out your copyright notice in the Description page of Project Settings.


#include "AbstractTower.h"

// Sets default values
AAbstractTower::AAbstractTower()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AttackRange = CreateDefaultSubobject<USphereComponent>(TEXT("AttackRange"));
}

// Called when the game starts or when spawned
void AAbstractTower::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAbstractTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

