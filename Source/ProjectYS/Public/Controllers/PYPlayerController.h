// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PYPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTYS_API APYPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	void BeginPlay();

public:
	class UPYHUD* GetHUDWidget() const { return HUDWidget; };

private:
	UPROPERTY();
	TObjectPtr<class UPYHUD> HUDWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "APYPlayerController", Meta = (AllowPrivateAccess));
	TSubclassOf<class UPYHUD> HUDWidgetClass;
};
