// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PYUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTYS_API UPYUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    AActor* GetOwningActor() const { return OwningActor; }

    void SetOwningActor(AActor* InOwningActor) { OwningActor = InOwningActor; }

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UPYUserWidget)
    TObjectPtr<AActor> OwningActor;
};
