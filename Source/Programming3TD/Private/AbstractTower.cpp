// Fill out your copyright notice in the Description page of Project Settings.


#include "AbstractTower.h"

// Sets default values
AAbstractTower::AAbstractTower()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AttackRange = CreateDefaultSubobject<USphereComponent>(TEXT("AttackRange"));
	AttackRange->SetupAttachment(GetRootComponent());
	AttackRange->SetGenerateOverlapEvents(true);

	TowerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TowerMesh"));
	TowerMesh->SetupAttachment(AttackRange);

	AttackDamage = 1;
	AttackSpeed = 1;
	ThreatLevel = 3;

	
}

// Called when the game starts or when spawned
void AAbstractTower::BeginPlay()
{
	Super::BeginPlay();
	//Defining overlap functions so that they work with only c++
	AttackRange->OnComponentBeginOverlap.AddDynamic(this, &AAbstractTower::OnBeginOverlap);
	AttackRange->OnComponentEndOverlap.AddDynamic(this, &AAbstractTower::OnEndOverlap);
}

void AAbstractTower::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	AttackRange->OnComponentBeginOverlap.RemoveDynamic(this, &AAbstractTower::OnBeginOverlap);
	AttackRange->OnComponentEndOverlap.RemoveDynamic(this, &AAbstractTower::OnEndOverlap);
}

void AAbstractTower::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlapped"));
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Overlapped"));

	//This gave false negatives, so it is currently disabled
	/*if (bFromSweep == false)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Does not exist"));
		return;
	}
	else */if (OtherActor == Cast<AAbstractEnemy>(OtherActor))
	{
		EnemiesList.PushLast(Cast<AAbstractEnemy>(OtherActor));
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Target Acquired"));
		return;
	}

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Wrong class"));
}

void AAbstractTower::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(OtherActor == Cast<AAbstractEnemy>(OtherActor))
	{
		EnemiesList.PopFirst();
	}
}

bool AAbstractTower::TowerAttack(float DeltaTime)
{
	AttackTimer -= DeltaTime;

	if (AttackTimer <= 0)
	{
	
		if (EnemiesList.IsEmpty())
		{
			AttackTimer = 0;
			return false;
		}

		EnemiesList.First()->AttackThis(AttackDamage);

		AttackTimer += AttackSpeed;
		return true;
	}

	return false;
	
}

// Called every frame
void AAbstractTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TowerAttack(DeltaTime);

}

int32 AAbstractTower::GetThreatlevel()
{
	return ThreatLevel;
}
