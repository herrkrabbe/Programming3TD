// Fill out your copyright notice in the Description page of Project Settings.


#include "PrototypeCharacter.h"

#include "InputState.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APrototypeCharacter::APrototypeCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PrototypeSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	PrototypeSpringArm->SetupAttachment(GetRootComponent());

	/*Camera Component*/
	PrototypeCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	PrototypeCameraComponent->SetupAttachment(PrototypeSpringArm);
	

	/*Skeletal Mesh Component*/
	PrototypeMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharMesh"));
	PrototypeMesh->SetupAttachment(GetRootComponent());

}

void APrototypeCharacter::Move(const FInputActionValue& Value)
{

	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void APrototypeCharacter::LookAround(const FInputActionValue& Value)
{
	FVector2D LookAroundVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(-LookAroundVector.X);
		AddControllerPitchInput(LookAroundVector.Y);
	}
}

//Prototype for trying to do things with mouse, however we are looking at another solution currently using "bEnableClickEvents" and "bEnableMouseOverEvents"
void APrototypeCharacter::Target()
{
	/*FVector MouseLocation;
	FVector MouseDirection;

	UGameplayStatics::GetPlayerController(GetWorld(), 0)->DeprojectMousePositionToWorld(MouseLocation, MouseDirection);

	FVector TraceStart = MouseLocation;
	FVector TraceEnd = MouseLocation + MouseDirection * 1000.0f;

	FCollisionQueryParams QueryParams;

	FHitResult TraceHit;

	TEnumAsByte<ECollisionChannel> TraceChannelProperty;

	GetWorld()->LineTraceSingleByChannel(TraceHit, TraceStart, TraceEnd, TraceChannelProperty, QueryParams);

	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, TraceHit.bBlockingHit ? FColor::Blue : FColor::Red, false, 5.0f, 0, 10.0f);

	if (TraceHit.bBlockingHit && IsValid(TraceHit.GetActor()))
	{
		UE_LOG(LogTemp, Log, TEXT("Trace hit actor: %s"), *TraceHit.GetActor()->GetName());
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("No Actors were hit"));
	}*/
}

// Called when the game starts or when spawned
void APrototypeCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Adding the Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}

	/* Mouse Cursor booleans*/
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		PlayerController->bShowMouseCursor = true;
		PlayerController->bEnableClickEvents = true;
		PlayerController->bEnableMouseOverEvents = true;
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Something didn't work"));
	}
}

// Called every frame
void APrototypeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APrototypeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APrototypeCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APrototypeCharacter::LookAround);
		EnhancedInputComponent->BindAction(TargetAction, ETriggerEvent::Triggered, this, &APrototypeCharacter::Target);
	}
}

