// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PYStatComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOutOfCurrentHPDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCurrentHPChangeDelegate, float, InOldCurrentHP, float, InNewCurrentHP);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMaxHPChangeDelegate, float, InOldMaxHP, float, InNewMaxHP);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCurrentEXPChangeDelegate, float, InOldCurrentEXP, float, InNewCurrentEXP);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMaxEXPChangeDelegate, float, InOldMaxEXP, float, InNewMaxEXP);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCurrentLVChangeDelegate, float, InOldCurrentLV, float, InNewCurrentLV);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMaxLVChangeDelegate, float, InOldMaxLV, float, InNewMaxLV);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNAMEChangeDelegate, FString, InOldNAME, FString, InNewNAME);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnATKChangeDelegate, float, InOldATK, float, InNewATK);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTYS_API UPYStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPYStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
public:
	float GetMaxHP() const { return MaxHP; }

	void SetMaxHP(float InMaxHP);

	float GetCurrentHP() const { return CurrentHP; }

	void SetCurrentHP(float InCurrentHP);

	float GetMaxEXP() const { return MaxEXP; }

	void SetMaxEXP(float InMaxHP);

	float GetCurrentEXP() const { return CurrentEXP; }

	void SetCurrentEXP(float InCurrentEXP);

	float GetMaxLV() const { return MaxLV; }

	void SetMaxLV(float InMaxLV);

	float GetCurrentLV() const { return CurrentLV; }

	void SetCurrentLV(float InCurrentLV);

	float GetATK() const { return CurrentATK; }

	void SetATK(float InATK);

	FString GetNAME() const { return NAME; }

	void SetNAME(FString InNAME);

public:
	FOnOutOfCurrentHPDelegate OnOutOfCurrentHPDelegate;

	FOnCurrentHPChangeDelegate OnCurrentHPChangeDelegate;

	FOnMaxHPChangeDelegate OnMaxHPChangeDelegate;

	FOnCurrentEXPChangeDelegate OnCurrentEXPChangeDelegate;

	FOnMaxEXPChangeDelegate OnMaxEXPChangeDelegate;

	FOnCurrentLVChangeDelegate OnCurrentLVChangeDelegate;

	FOnMaxLVChangeDelegate OnMaxLVChangeDelegate;

	FOnNAMEChangeDelegate OnNAMEChangeDelegate;

	FOnATKChangeDelegate OnATKChangeDelegate;

private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "UPYStatComponent", Meta = (AllowPrivateAccess))
	TObjectPtr<class UPYGameInstance> GameInstance;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = "UPYStatComponent", Meta = (AllowPrivateAccess))
	FString NAME;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "UPYStatComponent", Meta = (AllowPrivateAccess))
	float MaxLV;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = "UPYStatComponent", Meta = (AllowPrivateAccess))
	float CurrentLV;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = "UPYStatComponent", Meta = (AllowPrivateAccess))
	float CurrentATK;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "UPYStatComponent", Meta = (AllowPrivateAccess))
	float MaxEXP;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = "UPYStatComponent", Meta = (AllowPrivateAccess))
	float CurrentEXP;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "UPYStatComponent", Meta = (AllowPrivateAccess))
	float MaxHP;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = "UPYStatComponent", Meta = (AllowPrivateAccess))
	float CurrentHP;
};
