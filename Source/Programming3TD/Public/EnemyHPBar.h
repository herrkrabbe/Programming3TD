// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/ProgressBar.h>
#include "EnemyHPBar.generated.h"
/**
* Sourced From
 * https://www.youtube.com/watch?v=i8NM4qtsrpo
 */
UCLASS()
class PROGRAMMING3TD_API UEnemyHPBar : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	void UpdateHPBar(const float CurrentHP, const float MaxHP);

private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	UProgressBar* HPBar = nullptr;
};
