// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PYW_EXPBar.h"
#include "Components/ProgressBar.h"
#include "Characters/PYCharacter.h"
#include "Components/PYStatComponent.h"

void UPYW_EXPBar::SetMaxEXP(float InMaxEXP)
{
	SetMaxFigure(InMaxEXP);
}

void UPYW_EXPBar::InitializeEXPBarWidget(UPYStatComponent* NewStatComponent)
{
    OnCurrentEXPChange(0, NewStatComponent->GetCurrentEXP());
}

void UPYW_EXPBar::OnMaxEXPChange(float InOldMaxEXP, float InNewMaxEXP)
{
    SetMaxFigure(InNewMaxEXP);

    OnCurrentEXPChange(0, InNewMaxEXP);
}

void UPYW_EXPBar::OnCurrentEXPChange(float InOldEXP, float InNewEXP)
{
    if (true == ::IsValid(Bar))
    {
        if (KINDA_SMALL_NUMBER < MaxFigure)
        {
            Bar->SetPercent(InNewEXP / MaxFigure);
        }
        else
        {
            Bar->SetPercent(0.f);
        }
    }
}

void UPYW_EXPBar::NativeConstruct()
{
    Super::NativeConstruct();

    APYCharacter* OwningCharacter = Cast<APYCharacter>(OwningActor);
    if (true == ::IsValid(OwningCharacter))
    {
        OwningCharacter->SetWidget(this);
    }
}
