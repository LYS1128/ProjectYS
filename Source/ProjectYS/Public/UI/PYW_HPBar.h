// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/PYW_Bar.h"
#include "PYW_HPBar.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTYS_API UPYW_HPBar : public UPYW_Bar
{
	GENERATED_BODY()
	
public:
    void SetMaxHP(float InMaxHP);

    void InitializeHPBarWidget(class UPYStatComponent* NewStatComponent);

    UFUNCTION()
    void OnMaxHPChange(float InOldMaxHP, float InNewMaxHP);

    UFUNCTION()
    void OnCurrentHPChange(float InOldHP, float InNewHP);

protected:
    virtual void NativeConstruct() override;
};
