// Fill out your copyright notice in the Description page of Project Settings.


#include "AbstractTower.h"

// Sets default values
AAbstractTower::AAbstractTower()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AttackRange = CreateDefaultSubobject<USphereComponent>(TEXT("AttackRange"));
	AttackRange->SetupAttachment(GetRootComponent());

	AttackDamage = 1;
	AttackSpeed = 1;
	ThreatLevel = 3;
}

// Called when the game starts or when spawned
void AAbstractTower::BeginPlay()
{
	Super::BeginPlay();
	AttackRange->OnComponentBeginOverlap.AddDynamic(this, &AAbstractTower::OnBeginOverlap);
	AttackRange->OnComponentEndOverlap.AddDynamic(this, &AAbstractTower::OnEndOverlap);
	
}

void AAbstractTower::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	AttackRange->OnComponentBeginOverlap.RemoveDynamic(this, &AAbstractTower::OnBeginOverlap);
	AttackRange->OnComponentEndOverlap.RemoveDynamic(this, &AAbstractTower::OnEndOverlap);
}

void AAbstractTower::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlapped"));
	if (bFromSweep == true)
		return;
	else if (OtherActor == Cast<AAbstractEnemy>(OtherActor))
	{
		EnemiesList.PushLast(Cast<AAbstractEnemy>(OtherActor));
	}
}

void AAbstractTower::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	EnemiesList.PopFirst();
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

}

int32 AAbstractTower::GetThreatlevel()
{
	return ThreatLevel;
}
