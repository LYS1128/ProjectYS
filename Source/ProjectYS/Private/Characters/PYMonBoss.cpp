// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PYMonBoss.h"
#include "Controllers/PYAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Animations/PYAnimInstance.h"
#include "Components//PYStatComponent.h"
#include "Components/PYWidgetComponent.h"
#include "UI/PYUserWidget.h"
#include "UI/PYW_HPBar.h"
#include "Games/PYGameInstance.h"
#include "Components//PYStatComponent.h"

APYMonBoss::APYMonBoss()
{
    PrimaryActorTick.bCanEverTick = false;

    AIControllerClass = APYAIController::StaticClass();
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

    WidgetComponent = CreateDefaultSubobject<UPYWidgetComponent>(TEXT("WidgetComponent"));
    WidgetComponent->SetupAttachment(GetRootComponent());
    WidgetComponent->SetRelativeLocation(FVector(0.f, 0.f, 150.f));
    WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
    WidgetComponent->SetDrawSize(FVector2D(300.0f, 100.0f));
    WidgetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void APYMonBoss::BeginPlay()
{
    Super::BeginPlay();

    auto GameInstance = Cast<UPYGameInstance>(GetWorld()->GetGameInstance());
    if (true == ::IsValid(GameInstance))
    {
        if (nullptr != GameInstance->GetCharacterStatDataTable() || nullptr != GameInstance->GetCharacterStatDataTableRow(1))
        {
            float NewMaxLV = GameInstance->GetMonsterStatDataTableRow(MONSTERINDEX::MONMINION)->LV;
            StatComponent->SetMaxHP(NewMaxLV);
            StatComponent->SetCurrentLV(NewMaxLV);
            float NewMaxHP = GameInstance->GetMonsterStatDataTableRow(MONSTERINDEX::MONMINION)->MaxHP;
            StatComponent->SetMaxHP(NewMaxHP);
            StatComponent->SetCurrentHP(NewMaxHP);
            float NewMaxEXP = GameInstance->GetMonsterStatDataTableRow(MONSTERINDEX::MONMINION)->EXP;
            StatComponent->SetMaxEXP(NewMaxEXP);
            StatComponent->SetCurrentEXP(0);
            float NewATK = GameInstance->GetMonsterStatDataTableRow(MONSTERINDEX::MONMINION)->ATK;
            StatComponent->SetATK(NewATK);
            FString NewName = GameInstance->GetMonsterStatDataTableRow(MONSTERINDEX::MONMINION)->MonName;
            StatComponent->SetNAME(NewName);
        }
    }

    if (false == IsPlayerControlled())
    {
        bUseControllerRotationYaw = false;

        GetCharacterMovement()->bOrientRotationToMovement = false;
        GetCharacterMovement()->bUseControllerDesiredRotation = true;
        GetCharacterMovement()->RotationRate = FRotator(0.f, 480.f, 0.f);

        GetCharacterMovement()->MaxWalkSpeed = 300.f;
    }

    UPYAnimInstance* AnimInstance = Cast<UPYAnimInstance>(GetMesh()->GetAnimInstance());
    if (true == ::IsValid(AnimInstance) && false == AnimInstance->OnMontageEnded.IsAlreadyBound(this, &ThisClass::OnAttackAnimMontageEnded))
    {
        AnimInstance->OnMontageEnded.AddDynamic(this, &ThisClass::OnAttackAnimMontageEnded);
        //AnimInstance->OnCheckHitDelegate.AddDynamic(this, &ThisClass::CheckHit);
    }
}

float APYMonBoss::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    float FinalDamageAmount = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

    if (StatComponent->GetCurrentHP() < KINDA_SMALL_NUMBER)
    {
        APYCharacter* DamageCauserCharacter = Cast<APYCharacter>(DamageCauser);
        if (true == ::IsValid(DamageCauserCharacter))
        {
            auto PlayerStatComponent = DamageCauserCharacter->GetStatComponent();
            float PlayaerCurrentEXP = PlayerStatComponent->GetCurrentEXP();
            DamageCauserCharacter->GetStatComponent()->SetCurrentEXP(PlayaerCurrentEXP + StatComponent->GetMaxEXP());
        }

        APYAIController* AIController = Cast<APYAIController>(GetController());
        if (true == ::IsValid(AIController))
        {
            AIController->EndAI();
        }
    }

    return FinalDamageAmount;
}

void APYMonBoss::SetWidget(UPYUserWidget* InStudyUserWidget)
{
    UPYW_HPBar* HPBarWidget = Cast<UPYW_HPBar>(InStudyUserWidget);
    if (true == ::IsValid(HPBarWidget))
    {
        HPBarWidget->SetMaxHP(StatComponent->GetMaxHP());
        HPBarWidget->InitializeHPBarWidget(StatComponent);
        StatComponent->OnCurrentHPChangeDelegate.AddDynamic(HPBarWidget, &UPYW_HPBar::OnCurrentHPChange);
    }
}

void APYMonBoss::Attack()
{
    if (0 == CurrentComboCount)
    {
        return;
    }
    else
    {
        ensure(FMath::IsWithinInclusive<int32>(CurrentComboCount, 1, MaxComboCount));
        bIsPlayerDetect = true;
    }
}

void APYMonBoss::CheckHit()
{
    Super::CheckHit();
}

void APYMonBoss::OnAttackAnimMontageEnded(UAnimMontage* Montage, bool bIsInterrupt)
{
    GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
    bIsAttacking = false;
}
