// Fill out your copyright notice in the Description page of Project Settings.


#include "AbstractEnemy.h"

#include <TDPlayerController.h>

#include "Kismet/GameplayStatics.h"
#include <Subsystems/PanelExtensionSubsystem.h>
#include "Components/WidgetComponent.h"
#include <Logging/StructuredLog.h>

// Sets default values
AAbstractEnemy::AAbstractEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	OverlapSphere = CreateDefaultSubobject<USphereComponent>(TEXT("OverlapSphere"));
	OverlapSphere->InitSphereRadius(2.0f);
	this->RootComponent = OverlapSphere;
	HPBarWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBar"));

	if (HPBarWidgetComponent) //Setup HPBar Widget Component
	{
		HPBarWidgetComponent->SetupAttachment(RootComponent);
		HPBarWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
		HPBarWidgetComponent->SetRelativeLocation(HPBarPosition);
	}

	if (HPBarClass == nullptr)
	{
		UE_LOGFMT(LogTemp, Display, "HPBarClass null in constructor`");
	}
}

// Called when the game starts or when spawned
void AAbstractEnemy::BeginPlay()
{
	Super::BeginPlay();
	queueIndex = 0;
	isAlive = false;
	speed = 100;
	healthMax = 1;
	healthCurrent = healthMax;
	DamageDealt = 5;

	//Set class for widget component to WBP EnemyHPBar
	if (HPBarClass == nullptr) //fallback option if HPBarClass is not set in editor
	{
		UE_LOGFMT(LogTemp, Warning, "HPBarClass is not set for '{0}'", GetActorLabel());
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("HPBarClass is not set"));
		static ConstructorHelpers::FClassFinder<UUserWidget> HPBarFile{ TEXT("/Game/HUD/WBP_EnemyHealthBar") };
		if (HPBarFile.Succeeded()) {
			HPBarWidgetComponent->SetWidgetClass(HPBarFile.Class);
		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("HPBarClass fallback failed"));
			UE_LOGFMT(LogTemp, Warning, "HPBarClass fallback failed for '{0}'", GetActorLabel());
			return;
		}
	}
	//Set class for widget component to WBP EnemyHPBar
	HPBarWidgetComponent->SetWidgetClass(HPBarClass);

	//store HPBar so that it only needs to be casted once
	HPBar = Cast<UEnemyHPBar>(HPBarWidgetComponent->GetUserWidgetObject());
	if (HPBar == nullptr) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, TEXT("HPBar failed to cast"));
		return;
	}
	
	HPBar->UpdateHPBar(healthCurrent, healthMax);
}

void AAbstractEnemy::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void AAbstractEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isAlive)
	{
		MoveToNextNode(DeltaTime);
	}

}

void AAbstractEnemy::SetPathQueue(PathQueue newPathQueue)
{
	this->pathQueue = newPathQueue;
	if (pathQueue.IsEmpty()) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Failed to set PathQueue"));
		UE_LOGFMT(LogTemp, Fatal, "Failed to set path");
	}
}

bool AAbstractEnemy::AttackThis(int64 damage)
{
	this->healthCurrent -= damage;
	if (this->healthCurrent <= 0)
	{
		this->healthCurrent = 0;
		RemoveThis();
	}
	HPBar->UpdateHPBar(healthCurrent, healthMax);
	return !isAlive;
}

void AAbstractEnemy::RemoveThis()
{
	if (TObjectPtr<ATDPlayerController> PlayerController = Cast<ATDPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
		PlayerController->AddDeadEnemyToWaveManager(this);
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Wrong PlayerController is being used"));
	}
	isAlive = false;
}

void AAbstractEnemy::Spawn()
{
	if (pathQueue.IsEmpty()) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("PathQueue is empty!"));
		return;
	}
	this->healthCurrent = this->healthMax;
	this->isAlive = true;
	this->queueIndex = 0;
	TObjectPtr<AGraphNode> startNode = this->pathQueue.GetCurrentNode();
	FVector startLocation = startNode->GetActorLocation();
	this->SetActorLocation(startLocation);
	HPBar->UpdateHPBar(healthCurrent, healthMax);
}

double AAbstractEnemy::DistanceToNextNode() const
{
	TObjectPtr<AGraphNode> nextNode = pathQueue.GetCurrentNode();
	return FVector::Dist(this->GetActorLocation(), nextNode->GetActorLocation());
}

int64 AAbstractEnemy::GetQueueIndex() const
{
	return queueIndex;
}

bool AAbstractEnemy::operator<(const AAbstractEnemy& other) const
{
	if (this->queueIndex > other.queueIndex)
		return true;

	if (DistanceToNextNode() > other.DistanceToNextNode())
		return true;

	return false;
}

void AAbstractEnemy::TeleportGlobal(FVector newLocation)
{
	this->SetActorLocation(newLocation);
}

void AAbstractEnemy::MoveToNextNode(float DeltaTime)
{
	//if (this->queueIndex >= this->pathQueue.Num())
	//{
	//	return;
	//}

	//Checks if the queue is empty before using it, in order to avoid errors
	if (pathQueue.IsEmpty()) {

		TObjectPtr<ATDPlayerController> PlayerController = Cast<ATDPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		PlayerController->LoseHealth(DamageDealt);
		this->RemoveThis();
	}

	TObjectPtr<AGraphNode> nextNode = this->pathQueue.GetCurrentNode();
	FVector direction = nextNode->GetActorLocation() - this->GetActorLocation();
	direction.Normalize();
	this->SetActorLocation(this->GetActorLocation() + direction * speed * DeltaTime);

	if (FVector::Dist(this->GetActorLocation(), nextNode->GetActorLocation()) < 1)
	{
		this->pathQueue.GoNextNode();
	}

	//There is also a check if queue is empty here, one of these is redundant, however I have yet to find out which one
	if (pathQueue.IsEmpty())
	{
		TObjectPtr<ATDPlayerController> PlayerController = Cast<ATDPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		PlayerController->LoseHealth(DamageDealt);
		this->RemoveThis();
	}
}