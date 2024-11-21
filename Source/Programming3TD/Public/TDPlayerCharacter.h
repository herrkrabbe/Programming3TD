// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "TDPlayerController.h"
#include "GameFramework/SpringArmComponent.h"

#include "TDPlayerCharacter.generated.h"

UCLASS()
class PROGRAMMING3TD_API ATDPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	//How many tower can currently be built
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 BuildableTowers = 3;
private:
	//How many more towers can be built after a wave has ended
	int32 BuildableTowersPerWave = 3;
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
	 * Reference to PlayerController, as it is used often
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<ATDPlayerController> SavedPlayerController;

	UFUNCTION(BlueprintCallable)
	void AddBuildableTowers();
	/*
	 * Input Mapping Context and Actions
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* TargetAction;

	void Move(const FInputActionValue& Value);

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
