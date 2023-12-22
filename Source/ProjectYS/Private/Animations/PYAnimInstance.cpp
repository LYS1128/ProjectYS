// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/PYAnimInstance.h"
#include "Characters/PYCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/PYStatComponent.h"

UPYAnimInstance::UPYAnimInstance()
{
}

void UPYAnimInstance::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();

    CurrentSpeed = 0.f;

    Velocity = FVector::ZeroVector;

    bIsFalling = false;

    bIsCrouching = false;

    APYCharacter* OwnerCharacter = Cast<APYCharacter>(TryGetPawnOwner());
    if (true == ::IsValid(OwnerCharacter))
    {
        UPYStatComponent* StatComponent = OwnerCharacter->GetStatComponent();
        if (true == ::IsValid(StatComponent))
        {
            if (false == StatComponent->OnOutOfCurrentHPDelegate.IsAlreadyBound(this, &ThisClass::OnCharacterDeath))
            {
                StatComponent->OnOutOfCurrentHPDelegate.AddDynamic(this, &ThisClass::OnCharacterDeath);
            }
        }
    }
}

void UPYAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    APYCharacter* OwnerCharacter = Cast<APYCharacter>(TryGetPawnOwner());
    if (true == ::IsValid(OwnerCharacter))
    {
        UCharacterMovementComponent* CharacterMovementComponent = OwnerCharacter->GetCharacterMovement();
        if (true == ::IsValid(CharacterMovementComponent))
        {
            Velocity = CharacterMovementComponent->GetLastUpdateVelocity();
            CurrentSpeed = Velocity.Size();
            bIsFalling = CharacterMovementComponent->IsFalling();
            bIsCrouching = CharacterMovementComponent->IsCrouching();
        }
    }
}

void UPYAnimInstance::PlayAttackAnimMontage()
{
    if (true == ::IsValid(AttackAnimMontage))
    {
        if (false == Montage_IsPlaying(AttackAnimMontage))
        {
            Montage_Play(AttackAnimMontage);
        }
    }
}

void UPYAnimInstance::AnimNotify_CheckHit()
{
    if (true == OnCheckHitDelegate.IsBound())
    {
        OnCheckHitDelegate.Broadcast();
    }
}

void UPYAnimInstance::AnimNotify_CheckCanNextCombo()
{
    if (true == OnCheckCanNextComboDelegate.IsBound())
    {
        OnCheckCanNextComboDelegate.Broadcast();
    }
}

void UPYAnimInstance::OnCharacterDeath()
{
    bIsDead = true;
}
