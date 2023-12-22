// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/PYUserWidget.h"
#include "PYW_Bar.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTYS_API UPYW_Bar : public UPYUserWidget
{
	GENERATED_BODY()
	
public:
    UPYW_Bar(const FObjectInitializer& ObjectInitializer);
    // 만약 Widget 클래스에서 생성자에 로직을 작성한다면 꼭 이 생성자를 선언/정의해줘야함.

    void SetMaxFigure(float InMaxFigure);

protected:
    virtual void NativeConstruct() override;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UPYW_Bar")
    TObjectPtr<class UProgressBar> Bar;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UPYW_Bar")
    float MaxFigure;
};
