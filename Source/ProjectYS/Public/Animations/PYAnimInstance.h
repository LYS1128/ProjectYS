// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PYAnimInstance.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCheckHitDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCheckCanNextComboDelegate);

/**
 * 
 */
UCLASS()
class PROJECTYS_API UPYAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
    UPYAnimInstance();

    friend class APYPlayer;
    friend class APYMonMinion;

public:
    virtual void NativeInitializeAnimation() override;

    virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
    void PlayAttackAnimMontage();

    UFUNCTION()
    void AnimNotify_CheckHit();

    UFUNCTION()
    void AnimNotify_CheckCanNextCombo();

    UFUNCTION()
    void OnCharacterDeath();

private:
    FOnCheckHitDelegate OnCheckHitDelegate;


    FOnCheckCanNextComboDelegate OnCheckCanNextComboDelegate;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UPYAnimInstance")
    float CurrentSpeed;
	
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UPYAnimInstance")
    FVector Velocity;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UPYAnimInstance")
    uint8 bIsFalling : 1;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UPYAnimInstance")
    uint8 bIsCrouching : 1;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UPYAnimInstance", Meta = (AllowPrivateAccess))
    uint8 bIsDead : 1;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UPYAnimInstance", Meta = (AllowPrivateAccess))
    TObjectPtr<class UAnimMontage> AttackAnimMontage;
};
