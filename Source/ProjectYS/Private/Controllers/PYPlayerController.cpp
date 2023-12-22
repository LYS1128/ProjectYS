// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/PYPlayerController.h"
#include "UI/PYHUD.h"
#include "Components/PYStatComponent.h"
#include "Characters/PYMonMinion.h"

void APYPlayerController::BeginPlay()
{
    if (true == ::IsValid(HUDWidgetClass))
    {
        HUDWidget = CreateWidget<UPYHUD>(this, HUDWidgetClass);
        if (true == ::IsValid(HUDWidget))
        {
            HUDWidget->AddToViewport();

            APYCharacter* PC = GetPawn<APYCharacter>();
            if (true == ::IsValid(PC))
            {
                UPYStatComponent* StatComponent = PC->GetStatComponent();
                if (true == ::IsValid(StatComponent))
                {
                    HUDWidget->BindStatComponent(StatComponent);
                }
            }
        }
    }
}
