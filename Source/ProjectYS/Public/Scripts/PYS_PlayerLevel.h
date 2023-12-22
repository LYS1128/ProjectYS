// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "PYS_PlayerLevel.generated.h"

USTRUCT(BlueprintType)
struct FPYPlayerLevel : public FTableRowBase
{
    GENERATED_BODY()

public:
    FPYPlayerLevel()
    {
    }

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MaxHP;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MaxEXP;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ATK;

};