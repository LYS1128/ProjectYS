// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PYW_HPBar.h"
#include "Components/ProgressBar.h"
#include "Characters/PYCharacter.h"
#include "Components/PYStatComponent.h"

void UPYW_HPBar::SetMaxHP(float InMaxHP)
{
	SetMaxFigure(InMaxHP);
}

void UPYW_HPBar::InitializeHPBarWidget(UPYStatComponent* NewStatComponent)
{
	OnCurrentHPChange(0, NewStatComponent->GetCurrentHP());
}

void UPYW_HPBar::OnMaxHPChange(float InOldMaxHP, float InNewMaxHP)
{
	SetMaxFigure(InNewMaxHP);

	OnCurrentHPChange(0, InNewMaxHP);
}

void UPYW_HPBar::OnCurrentHPChange(float InOldHP, float InNewHP)
{
    if (true == ::IsValid(Bar))
    {
        if (KINDA_SMALL_NUMBER < MaxFigure)
        {
            Bar->SetPercent(InNewHP / MaxFigure);
        }
        else
        {
            Bar->SetPercent(0.f);
        }
    }
}

void UPYW_HPBar::NativeConstruct()
{
    Super::NativeConstruct();

    APYCharacter* OwningCharacter = Cast<APYCharacter>(OwningActor);
    if (true == ::IsValid(OwningCharacter))
    {
        OwningCharacter->SetWidget(this);
    }
}
