// Fill out your copyright notice in the Description page of Project Settings.


#include "Games/PYGameInstance.h"


void UPYGameInstance::Init()
{
	Super::Init();

    if (false == ::IsValid(CharacterStatDataTable) || CharacterStatDataTable->GetRowMap().Num() <= 0)
    {
        UE_LOG(LogTemp, Error, TEXT("Not enuough data in CharacterStatDataTable."));
    }
    else
    {
        for (int32 i = 1; i <= CharacterStatDataTable->GetRowMap().Num(); ++i)
        {
            check(nullptr != GetCharacterStatDataTableRow(i));
        }
    }
}

void UPYGameInstance::Shutdown()
{
	Super::Shutdown();
}

FPYPlayerLevel* UPYGameInstance::GetCharacterStatDataTableRow(int32 InLevel)
{
    if (true == ::IsValid(CharacterStatDataTable))
    {
        return CharacterStatDataTable->FindRow<FPYPlayerLevel>(*FString::FromInt(InLevel), TEXT(""));
    }

    return nullptr;
}

FPYMonsterInfo* UPYGameInstance::GetMonsterStatDataTableRow(int32 InLevel)
{
    if (true == ::IsValid(CharacterStatDataTable))
    {
        return MonsterStatDataTable->FindRow<FPYMonsterInfo>(*FString::FromInt(InLevel), TEXT(""));
    }

    return nullptr;
}
