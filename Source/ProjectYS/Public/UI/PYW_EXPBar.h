// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/PYW_Bar.h"
#include "PYW_EXPBar.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTYS_API UPYW_EXPBar : public UPYW_Bar
{
	GENERATED_BODY()
	
public:
    void SetMaxEXP(float InMaxEXP);

    void InitializeEXPBarWidget(class UPYStatComponent* NewStatComponent);

    UFUNCTION()
    void OnMaxEXPChange(float InOldMaxEXP, float InNewMaxEXP);

    UFUNCTION()
    void OnCurrentEXPChange(float InOldEXP, float InNewEXP);

protected:
    virtual void NativeConstruct() override;
};
