// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PYHUD.h"
#include "Components/PYStatComponent.h"
#include "UI/PYW_HPBar.h"
#include "UI/PYW_EXPBar.h"
#include "Components/TextBlock.h"
#include "Games/PYGameInstance.h"

void UPYHUD::BindStatComponent(UPYStatComponent* InStatComponent)
{
	if (true == ::IsValid(InStatComponent))
	{
		StatComponent = InStatComponent;
		StatComponent->OnCurrentHPChangeDelegate.AddDynamic(HPBar, &UPYW_HPBar::OnCurrentHPChange);
		StatComponent->OnMaxHPChangeDelegate.AddDynamic(HPBar, &UPYW_HPBar::OnMaxHPChange);
		StatComponent->OnCurrentEXPChangeDelegate.AddDynamic(EXPBar, &UPYW_EXPBar::OnCurrentEXPChange);
		StatComponent->OnMaxEXPChangeDelegate.AddDynamic(EXPBar, &UPYW_EXPBar::OnMaxEXPChange);
		StatComponent->OnCurrentLVChangeDelegate.AddDynamic(this, &ThisClass::UpdateLevelText);

		// PlayerController::BeginPlay()가 SStatComponent::BeginPlay()보다 먼저 호출되기에 아래와 같이 초기화.
		UPYGameInstance* GameInstance = Cast<UPYGameInstance>(GetWorld()->GetGameInstance());
		if (true == ::IsValid(GameInstance))
		{
			if (nullptr != GameInstance->GetCharacterStatDataTable() || nullptr != GameInstance->GetCharacterStatDataTableRow(1))
			{
				float MaxHP = GameInstance->GetCharacterStatDataTableRow(1)->MaxHP;
				HPBar->SetMaxHP(MaxHP);
				HPBar->InitializeHPBarWidget(StatComponent.Get());

				float MaxEXP = GameInstance->GetCharacterStatDataTableRow(1)->MaxEXP;
				EXPBar->SetMaxEXP(MaxEXP);
				EXPBar->InitializeEXPBarWidget(StatComponent.Get());

				UpdateLevelText(0, 1);
			}
		}
	}
}

void UPYHUD::UpdateLevelText(float InOldCurrentLV, float InNewCurrentLV)
{
	FString LevelString = FString::Printf(TEXT("%d"), (int32)InNewCurrentLV);

	LevelText->SetText(FText::FromString(LevelString));
}
