// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbstractEnemy.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "Containers/Deque.h"
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
	float AttackSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	float AttackTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	USphereComponent* AttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	int32 ThreatLevel;

	TDeque<TObjectPtr<AAbstractEnemy>> EnemiesList;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComp, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex);

	UFUNCTION()
	virtual bool TowerAttack(float DeltaTime);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	int32 GetThreatlevel();
};
