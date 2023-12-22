// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/PYMonster.h"
#include "PYMonMinion.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTYS_API APYMonMinion : public APYMonster
{
	GENERATED_BODY()

	friend class UBTTask_Attack;

public:
	APYMonMinion();
	
public:
	virtual void BeginPlay() override;

	bool IsNowAttacking() const { return bIsAttacking; }

	void SetPlayerDetect(bool PlayerDetect) { bIsPlayerDetect = PlayerDetect; }

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	virtual void SetWidget(class UPYUserWidget* InStudyUserWidget) override;

private:
	void Attack();

	void CheckHit();

	UFUNCTION()
	void OnAttackAnimMontageEnded(class UAnimMontage* Montage, bool bIsInterrupt);

	void BeginCombo();

	UFUNCTION()
	void CheckCanNextCombo();

	UFUNCTION()
	void EndCombo(class UAnimMontage* InAnimMontage, bool bInterrupted);

private:

	bool bIsAttacking = false;

	FString AttackAnimMontageSectionName = FString(TEXT("Attack"));

	int32 MaxComboCount = 4;

	int32 CurrentComboCount = 0;

	bool bIsPlayerDetect = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "APYMonMinion", Meta = (AllowPrivateAccess))
	TObjectPtr<class UPYWidgetComponent> WidgetComponent;
};
