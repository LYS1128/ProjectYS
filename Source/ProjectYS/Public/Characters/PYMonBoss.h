// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/PYMonster.h"
#include "PYMonBoss.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTYS_API APYMonBoss : public APYMonster
{
	GENERATED_BODY()
	
public:
	APYMonBoss();

public:
	virtual void BeginPlay() override;

	bool IsNowAttacking() const { return bIsAttacking; }

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	virtual void SetWidget(class UPYUserWidget* InStudyUserWidget) override;

private:
	void Attack();

	void CheckHit();

	UFUNCTION()
	void OnAttackAnimMontageEnded(class UAnimMontage* Montage, bool bIsInterrupt);

private:

	bool bIsAttacking = false;

	FString AttackAnimMontageSectionName = FString(TEXT("Attack"));

	int32 MaxComboCount = 4;

	int32 CurrentComboCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "APYMonBoss", Meta = (AllowPrivateAccess))
	TObjectPtr<class UPYWidgetComponent> WidgetComponent;
};
