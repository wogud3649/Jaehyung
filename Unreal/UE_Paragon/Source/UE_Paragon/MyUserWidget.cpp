// Fill out your copyright notice in the Description page of Project Settings.


#include "MyUserWidget.h"
#include "MyStatComponent.h"
#include "Components/ProgressBar.h"

void UMyUserWidget::Bind(class UMyStatComponent* statComponent)
{
	statComponent->_onHpChangedRatio.AddUObject(this, &UMyUserWidget::SetHpBarRatio);
}

void UMyUserWidget::SetHpBarRatio(float value)
{
	PB_HPBar->SetPercent(value);
}