// Fill out your copyright notice in the Description page of Project Settings./

#pragma once

#include "CoreMinimal.h"
#include "Characters/PYCharacter.h"
#include "InputActionValue.h"
#include "../Items/PYWeapon.h"
#include "PYPlayer.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTYS_API APYPlayer : public APYCharacter
{
	GENERATED_BODY()

    friend class UAN_CheckHit;
	
public:
    APYPlayer();

public:
    virtual void BeginPlay() override;


public:
    float GetForwardInputValue() const { return ForwardInputValue; }

    float GetRightInputValue() const { return RightInputValue; }

public:

    UFUNCTION()
    void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

protected:
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

private:
    void Move(const FInputActionValue& InValue);

    void Look(const FInputActionValue& InValue);

    void Attack(const FInputActionValue& InValue);

    virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

private:
    void CheckHit();

    void BeginCombo();

    UFUNCTION()
    void CheckCanNextCombo();

    UFUNCTION()
    void EndCombo(class UAnimMontage* InAnimMontage, bool bInterrupted);

private:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "APYPlayer", meta = (AllowPrivateAccess))
    TObjectPtr<class USpringArmComponent> SpringArmComponent;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "APYPlayer", meta = (AllowPrivateAccess))
    TObjectPtr<class UCameraComponent> CameraComponent;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "APYPlayer", Meta = (AllowPrivateAccess))
    TObjectPtr<class UPYInputConfigData> PlayerCharacterInputConfigData;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "APYPlayer", Meta = (AllowPrivateAccess))
    TObjectPtr<class UInputMappingContext> PlayerCharacterInputMappingContext;

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "APYPlayer", Meta = (AllowPrivateAccess = true))
    float ForwardInputValue;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "APYPlayer", Meta = (AllowPrivateAccess = true))
    float RightInputValue;

    uint8 bIsAttacking : 1;

    FString AttackAnimMontageSectionName = FString(TEXT("Attack"));

    int32 MaxComboCount = 4;

    int32 CurrentComboCount = 0;

    bool bIsAttackKeyPressed = false;
};
