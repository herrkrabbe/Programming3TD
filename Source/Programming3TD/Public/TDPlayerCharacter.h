// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Programming3TD/PrototypeCharacter.h"
#include "TDPlayerCharacter.generated.h"

UCLASS()
class PROGRAMMING3TD_API ATDPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATDPlayerCharacter();


	/*
	 *Components
	 */

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USpringArmComponent* CameraSpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* IsometricCameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* CharacterMesh;


	/*
	 * Input Mapping Context and Actions
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* TargetAction;

	void Move(const FInputActionValue& Value);

	void LookAround(const FInputActionValue& Value);

	void Target();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
