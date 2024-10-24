// Fill out your copyright notice in the Description page of Project Settings.


#include "TDPlayerCharacter.h"

// Sets default values
ATDPlayerCharacter::ATDPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	CameraSpringArm->SetupAttachment(GetRootComponent());

	/*Camera Component*/
	IsometricCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	IsometricCameraComponent->SetupAttachment(CameraSpringArm);

	CharacterMesh = GetMesh();
}

// Called when the game starts or when spawned
void ATDPlayerCharacter::BeginPlay()
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
void ATDPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATDPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATDPlayerCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATDPlayerCharacter::LookAround);
		EnhancedInputComponent->BindAction(TargetAction, ETriggerEvent::Triggered, this, &ATDPlayerCharacter::Target);
	}

}

void ATDPlayerCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void ATDPlayerCharacter::LookAround(const FInputActionValue& Value)
{
	FVector2D LookAroundVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(-LookAroundVector.X);
		AddControllerPitchInput(LookAroundVector.Y);
	}
}
void ATDPlayerCharacter::Target()
{
	ECollisionChannel StandardCollisionChannel;
	FHitResult TargetResults;

	GetLocalViewingPlayerController()->GetHitResultUnderCursor(StandardCollisionChannel, false, TargetResults);

	if (AActor* TargetActor = Cast<ATDPlayerCharacter>(TargetResults.GetActor()))
	{
		//TargetActor->Build()
		/*
		 *From here you just need the Build function in the BuildPlot, also changing the cast to BuildPlot instead of ATDPlayerCharacter
		 */
	}

}
