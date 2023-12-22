// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PYHUD.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTYS_API UPYHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
    void BindStatComponent(class UPYStatComponent* InStatComponent);

protected:
    UFUNCTION()
    virtual void UpdateLevelText(float InOldCurrentLV, float InNewCurrentLV);

protected:
    TWeakObjectPtr<class UPYStatComponent> StatComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UPYHUD", Meta = (BindWidget))
    TObjectPtr<class UTextBlock> LevelText;
    // BindWidget을 통해서 하드코딩으로 속성과 위젯을 바인드 하지 않아도 됨.

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UPYHUD", Meta = (BindWidget))
    TObjectPtr<class UTextBlock> PlayerNameText;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UPYHUD", Meta = (BindWidget))
    TObjectPtr<class UPYW_HPBar> HPBar;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UPYHUD", Meta = (BindWidget))
    TObjectPtr<class UPYW_EXPBar> EXPBar;
};
