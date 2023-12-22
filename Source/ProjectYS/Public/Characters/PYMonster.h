// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/PYCharacter.h"
#include "PYMonster.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTYS_API APYMonster : public APYCharacter
{
	GENERATED_BODY()

public:
	enum MONSTERINDEX
	{
		MONMINION = 1,

		MONCOUNT
	};


};
