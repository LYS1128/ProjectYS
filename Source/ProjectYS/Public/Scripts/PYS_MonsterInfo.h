#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "PYS_MonsterInfo.generated.h"

USTRUCT(BlueprintType)
struct FPYMonsterInfo : public FTableRowBase
{
    GENERATED_BODY()

public:
    FPYMonsterInfo()
    {
    }

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString MonName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float LV;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MaxHP;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float EXP;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ATK;

};