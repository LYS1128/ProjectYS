// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PYInputConfigData.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTYS_API UPYInputConfigData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<class UInputAction> MoveAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<class UInputAction> LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<class UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<class UInputAction> AttackAction;
};
