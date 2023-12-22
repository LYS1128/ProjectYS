// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/PYWidgetComponent.h"
#include "UI/PYUserWidget.h"

void UPYWidgetComponent::InitWidget()
{
    Super::InitWidget();

    UPYUserWidget* SWidget = Cast<UPYUserWidget>(GetWidget());
    if (true == ::IsValid(SWidget))
    {
        SWidget->SetOwningActor(GetOwner());
    }
}
