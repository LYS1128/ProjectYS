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
    // BindWidget�� ���ؼ� �ϵ��ڵ����� �Ӽ��� ������ ���ε� ���� �ʾƵ� ��.

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UPYHUD", Meta = (BindWidget))
    TObjectPtr<class UTextBlock> PlayerNameText;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UPYHUD", Meta = (BindWidget))
    TObjectPtr<class UPYW_HPBar> HPBar;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UPYHUD", Meta = (BindWidget))
    TObjectPtr<class UPYW_EXPBar> EXPBar;
};
