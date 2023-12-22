// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PYStatComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Games/PYGameInstance.h"

// Sets default values for this component's properties
UPYStatComponent::UPYStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPYStatComponent::BeginPlay()
{
	Super::BeginPlay();

	GameInstance = Cast<UPYGameInstance>(GetWorld()->GetGameInstance());
	
}

// Called every frame
void UPYStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPYStatComponent::SetMaxHP(float InMaxHP)
{
	if (true == OnMaxHPChangeDelegate.IsBound())
	{
		OnMaxHPChangeDelegate.Broadcast(MaxHP, InMaxHP);
	}

	MaxHP = FMath::Clamp<float>(InMaxHP, 0.f, 9999);
}

void UPYStatComponent::SetCurrentHP(float InCurrentHP)
{
	if (true == OnCurrentHPChangeDelegate.IsBound())
	{
		OnCurrentHPChangeDelegate.Broadcast(CurrentHP, InCurrentHP);	
	}

	CurrentHP = FMath::Clamp<float>(InCurrentHP, 0.f, MaxHP);

	if (CurrentHP < KINDA_SMALL_NUMBER)
	{
		OnOutOfCurrentHPDelegate.Broadcast();
		CurrentHP = 0.f;
	}
}

void UPYStatComponent::SetMaxEXP(float InMaxEXP)
{
	if (true == OnMaxEXPChangeDelegate.IsBound())
	{
		OnMaxEXPChangeDelegate.Broadcast(MaxHP, InMaxEXP);
	}

	MaxEXP = FMath::Clamp<float>(InMaxEXP, 0.f, 9999);
}

void UPYStatComponent::SetCurrentEXP(float InCurrentEXP)
{
	CurrentEXP = FMath::Clamp<float>(InCurrentEXP, 0.f, MaxEXP);

	if (MaxEXP - KINDA_SMALL_NUMBER < CurrentEXP)
	{
		SetCurrentLV(GetCurrentLV() + 1);
		SetMaxEXP(GameInstance->GetCharacterStatDataTableRow(GetCurrentLV())->MaxEXP);
		CurrentEXP = 0.f;
		SetMaxHP(GameInstance->GetCharacterStatDataTableRow(GetCurrentLV())->MaxHP);
		SetCurrentHP(GameInstance->GetCharacterStatDataTableRow(GetCurrentLV())->MaxHP);
		SetATK(GameInstance->GetCharacterStatDataTableRow(GetCurrentLV())->ATK);
	}

	if (true == OnCurrentEXPChangeDelegate.IsBound())
	{
		OnCurrentEXPChangeDelegate.Broadcast(CurrentEXP, InCurrentEXP);
	}
}

void UPYStatComponent::SetMaxLV(float InMaxLV)
{
	if (true == OnMaxLVChangeDelegate.IsBound())
	{
		OnMaxLVChangeDelegate.Broadcast(MaxLV, InMaxLV);
	}

	MaxLV = FMath::Clamp<float>(InMaxLV, 0.f, 9999);
}

void UPYStatComponent::SetCurrentLV(float InCurrentLV)
{
	if (true == OnCurrentLVChangeDelegate.IsBound())
	{
		OnCurrentLVChangeDelegate.Broadcast(CurrentLV, InCurrentLV);
	}

	CurrentLV = FMath::Clamp<float>(InCurrentLV, 0.f, MaxLV);
}

void UPYStatComponent::SetATK(float InATK)
{
	if (true == OnATKChangeDelegate.IsBound())
	{
		OnMaxLVChangeDelegate.Broadcast(CurrentATK, InATK);
	}

	CurrentATK = FMath::Clamp<float>(InATK, 0.f, 9999);
}

void UPYStatComponent::SetNAME(FString InNAME)
{
	if (true == OnNAMEChangeDelegate.IsBound())
	{
		OnNAMEChangeDelegate.Broadcast(NAME, InNAME);
	}

	NAME = InNAME;
}

