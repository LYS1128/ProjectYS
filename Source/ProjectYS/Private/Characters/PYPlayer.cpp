// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PYPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Inputs/PYInputConfigData.h"
#include "Animations/PYAnimInstance.h"
#include "Engine/EngineTypes.h"
#include "Engine/DamageEvents.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/CapsuleComponent.h"
#include "Games/PYGameInstance.h"
#include "Components//PYStatComponent.h"

APYPlayer::APYPlayer()
{
    PrimaryActorTick.bCanEverTick = false;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
    SpringArmComponent->SetupAttachment(RootComponent);
    SpringArmComponent->TargetArmLength = 400.f;
    SpringArmComponent->bUsePawnControlRotation = true;
    SpringArmComponent->bDoCollisionTest = true;
    SpringArmComponent->bInheritPitch = true;
    SpringArmComponent->bInheritYaw = true;
    SpringArmComponent->bInheritRoll = false;

    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
    CameraComponent->SetRelativeLocation(FVector(0.f, 100.f, 0.f));
    CameraComponent->SetupAttachment(SpringArmComponent);

    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->bUseControllerDesiredRotation = false;
    GetCharacterMovement()->RotationRate = FRotator(0.f, 480.f, 0.f);

    GetCapsuleComponent()->SetCollisionProfileName(TEXT("PYCharacter"));
}

void APYPlayer::BeginPlay()
{
    Super::BeginPlay();

    auto GameInstance = Cast<UPYGameInstance>(GetWorld()->GetGameInstance());
    if (true == ::IsValid(GameInstance))
    {
        if (nullptr != GameInstance->GetCharacterStatDataTable() || nullptr != GameInstance->GetCharacterStatDataTableRow(1))
        {
            StatComponent->SetMaxLV(GameInstance->GetCharacterStatDataTable()->GetRowMap().Num());
            StatComponent->SetCurrentLV(1);
            float NewMaxHP = GameInstance->GetCharacterStatDataTableRow(1)->MaxHP;
            StatComponent->SetMaxHP(NewMaxHP);
            StatComponent->SetCurrentHP(NewMaxHP);
            float NewMaxEXP = GameInstance->GetCharacterStatDataTableRow(1)->MaxEXP;
            StatComponent->SetMaxEXP(NewMaxEXP);
            StatComponent->SetCurrentEXP(0);
            float NewATK = GameInstance->GetCharacterStatDataTableRow(1)->ATK;
            StatComponent->SetATK(NewATK);
            StatComponent->SetNAME("Player");           
        }
    }

    APlayerController* PlayerController = Cast<APlayerController>(GetController());
    if (true == ::IsValid(PlayerController))
    {
        UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
        if (true == ::IsValid(Subsystem))
        {
            Subsystem->AddMappingContext(PlayerCharacterInputMappingContext, 0);
        }
    }

    UPYAnimInstance* AnimInstance = Cast<UPYAnimInstance>(GetMesh()->GetAnimInstance());
    if (true == ::IsValid(AnimInstance))
    {
        AnimInstance->OnMontageEnded.AddDynamic(this, &ThisClass::OnAttackMontageEnded);
        AnimInstance->OnCheckHitDelegate.AddDynamic(this, &ThisClass::CheckHit);
        AnimInstance->OnCheckCanNextComboDelegate.AddDynamic(this, &ThisClass::CheckCanNextCombo);
    }
}

void APYPlayer::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
     GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
       bIsAttacking = false;
}

void APYPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
    if (true == ::IsValid(EnhancedInputComponent))
    {
        EnhancedInputComponent->BindAction(PlayerCharacterInputConfigData->MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
        EnhancedInputComponent->BindAction(PlayerCharacterInputConfigData->LookAction, ETriggerEvent::Triggered, this, &ThisClass::Look);
        EnhancedInputComponent->BindAction(PlayerCharacterInputConfigData->JumpAction, ETriggerEvent::Started, this, &ThisClass::Jump);
        EnhancedInputComponent->BindAction(PlayerCharacterInputConfigData->AttackAction, ETriggerEvent::Started, this, &ThisClass::Attack);
    }
}

void APYPlayer::Move(const FInputActionValue& InValue)
{
    FVector2D MovementVector = InValue.Get<FVector2D>();
    ForwardInputValue = MovementVector.X;
    RightInputValue = MovementVector.Y;

    const FRotator CurrentControlRotation = GetController()->GetControlRotation();
    const FRotator CurrentControlRotationYaw(0.f, CurrentControlRotation.Yaw, 0.f);

    FVector ForwardDirection = FRotationMatrix(CurrentControlRotationYaw).GetUnitAxis(EAxis::X);
    FVector RightDirection = FRotationMatrix(CurrentControlRotationYaw).GetUnitAxis(EAxis::Y);

    AddMovementInput(ForwardDirection, MovementVector.X);
    AddMovementInput(RightDirection, MovementVector.Y);
}

void APYPlayer::Look(const FInputActionValue& InValue)
{
    FVector2D LookAxisVector = InValue.Get<FVector2D>();

    AddControllerYawInput(LookAxisVector.X);
    AddControllerPitchInput(LookAxisVector.Y);
}

void APYPlayer::Attack(const FInputActionValue& InValue)
{
    if (0 == CurrentComboCount)
    {
        BeginCombo();
        return;
    }
    else
    {
        ensure(FMath::IsWithinInclusive<int32>(CurrentComboCount, 1, MaxComboCount));
        bIsAttackKeyPressed = true;
    }
}

float APYPlayer::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    float FinalDamageAmount = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

    return FinalDamageAmount;
}

void APYPlayer::CheckHit()
{
    Super::CheckHit();
}

void APYPlayer::BeginCombo()
{
    UPYAnimInstance* AnimInstance = Cast<UPYAnimInstance>(GetMesh()->GetAnimInstance());
    if (false == ::IsValid(AnimInstance))
    {
        return;
    }

    CurrentComboCount = 1;

    GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);

    AnimInstance->PlayAttackAnimMontage();

    FOnMontageEnded OnMontageEndedDelegate;
    OnMontageEndedDelegate.BindUObject(this, &ThisClass::EndCombo);
    AnimInstance->Montage_SetEndDelegate(OnMontageEndedDelegate, AnimInstance->AttackAnimMontage);
}

void APYPlayer::CheckCanNextCombo()
{
    UPYAnimInstance* AnimInstance = Cast<UPYAnimInstance>(GetMesh()->GetAnimInstance());
    if (false == ::IsValid(AnimInstance))
    {
        return;
    }

    if (true == bIsAttackKeyPressed)
    {
        CurrentComboCount = FMath::Clamp(CurrentComboCount + 1, 1, MaxComboCount);

        FName NextSectionName = *FString::Printf(TEXT("%s%d"), *AttackAnimMontageSectionName, CurrentComboCount);
        AnimInstance->Montage_JumpToSection(NextSectionName, AnimInstance->AttackAnimMontage);
        bIsAttackKeyPressed = false;
    }
}

void APYPlayer::EndCombo(UAnimMontage* InAnimMontage, bool bInterrupted)
{
    ensure(0 != CurrentComboCount);
    CurrentComboCount = 0;
    bIsAttackKeyPressed = false;
    GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

void APYPlayer::OnCurrentLevelChanged(int32 InOldCurrentLevel, int32 InNewCurrentLevel)
{

}
