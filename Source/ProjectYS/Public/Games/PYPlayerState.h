// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PYPlayerState.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class PlayerMode : uint8 { MODE_HAND UMETA(DisplaybName = "HAND"), MODE_SWORD  UMETA(DisplaybName = "SWORD"), MODE_GUN  UMETA(DisplaybName = "GUN")};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCurrentModeChangedDelegate, PlayerMode, InOldCurrentMode, PlayerMode, InNewCurrentMode);

UCLASS()
class PROJECTYS_API APYPlayerState : public APlayerState
{
	GENERATED_BODY()

	friend class APYWeapon;

public:
	FOnCurrentModeChangedDelegate OnCurrentModeChangedDelegate;

public:
	APYPlayerState();

	void InitPlayerState();

	UFUNCTION(BlueprintCallable)
	PlayerMode GetPlayerMode() const { return CurrentMode; }

	void SetPlayerMode(PlayerMode Mode);

	APYWeapon* GetPlayerSword() const { return CurrentSword; }

	void SetPlayerSword(APYWeapon* Sword);

	APYWeapon* GetPlayerGun() const { return CurrentGun; }

	void SetPlayerGun(APYWeapon* Gun);

private:
	APYWeapon* CurrentSword;

	APYWeapon* CurrentGun;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "UPYPlayerState", Meta = (AllowPrivateAccess = true))
	PlayerMode CurrentMode = PlayerMode::MODE_HAND;

	
};
