// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Scripts/PYS_PlayerLevel.h"
#include "Scripts/PYS_MonsterInfo.h"
#include "PYGameInstance.generated.h"


/**
 * 
 */
UCLASS()
class PROJECTYS_API UPYGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;

	virtual void Shutdown() override;

public:
	const UDataTable* GetCharacterStatDataTable() { return CharacterStatDataTable; }

	FPYPlayerLevel* UPYGameInstance::GetCharacterStatDataTableRow(int32 InLevel);

	const UDataTable* GetMonsterStatDataTable() { return MonsterStatDataTable; }

	FPYMonsterInfo* UPYGameInstance::GetMonsterStatDataTableRow(int32 InLevel);
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UPYGameInstance", Meta = (AllowPrivateAccess))
	class UDataTable* CharacterStatDataTable;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UPYGameInstance", Meta = (AllowPrivateAccess))
	class UDataTable* MonsterStatDataTable;
};
