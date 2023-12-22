// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PYW_Bar.h"
#include "Components/ProgressBar.h"
#include "Characters/PYMonMinion.h"
#include "Components/PYStatComponent.h"

UPYW_Bar::UPYW_Bar(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer) // �ݵ�� �ʿ��� �ڵ�. ���� ���� �� �� �� �־������.
{
}

void UPYW_Bar::SetMaxFigure(float InMaxFigure)
{
    if (InMaxFigure < KINDA_SMALL_NUMBER)
    {
        MaxFigure = 0.f;
        return;
    }

    MaxFigure = InMaxFigure;
}

void UPYW_Bar::NativeConstruct()
{
    Super::NativeConstruct();

    Bar = Cast<UProgressBar>(GetWidgetFromName("BarWidget"));
    // �ϵ��ڵ����� ������ �Ӽ��� ���ε��ϴ� ���. ���Ŀ� ���� ���ε� �ϴ� ��� �Ұ� ����.
    check(nullptr != Bar);
}
