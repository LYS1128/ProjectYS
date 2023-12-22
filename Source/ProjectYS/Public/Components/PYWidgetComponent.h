// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "PYWidgetComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTYS_API UPYWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
	
public:
	virtual void InitWidget() override;
};
