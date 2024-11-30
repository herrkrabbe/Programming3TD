// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyHPBar.h"

void UEnemyHPBar::NativeConstruct()
{
	Super::NativeConstruct();
}

void UEnemyHPBar::UpdateHPBar(const float CurrentHP, const float MaxHP)
{
	HPBar->SetPercent(CurrentHP / MaxHP);
}
