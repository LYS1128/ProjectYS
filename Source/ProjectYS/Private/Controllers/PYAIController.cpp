// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/PYAIController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetSystemLibrary.h"

const float APYAIController::PatrolRadius(500.f);
const FName APYAIController::StartPatrolPositionKey(TEXT("StartPatrolPosition"));
const FName APYAIController::EndPatrolPositionKey(TEXT("EndPatrolPosition"));
const FName APYAIController::TargetActorKey(TEXT("TargetActor"));

APYAIController::APYAIController()
{
    Blackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard"));
    BrainComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BrainComponent"));
}

void APYAIController::BeginAI(APawn* InPawn)
{
    UBlackboardComponent* BlackboardComponent = Cast<UBlackboardComponent>(Blackboard);
    if (true == ::IsValid(BlackboardComponent))
    {
        if (true == UseBlackboard(BlackboardDataAsset, BlackboardComponent))
        {
            bool bRunSucceeded = RunBehaviorTree(BehaviorTree);
            ensure(true == bRunSucceeded);
            UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("BeginAI() has been called.")));
            BlackboardComponent->SetValueAsVector(StartPatrolPositionKey, InPawn->GetActorLocation());
        }
    }
}

void APYAIController::EndAI()
{
    UBehaviorTreeComponent* BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
    if (true == ::IsValid(BehaviorTreeComponent))
    {
        BehaviorTreeComponent->StopTree();
        UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("EndAI() has been called.")));
    }
}

void APYAIController::BeginPlay()
{
    Super::BeginPlay();

    APawn* ControlledPawn = GetPawn();
    if (true == ::IsValid(ControlledPawn))
    {
        BeginAI(ControlledPawn);
    }
}

void APYAIController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    EndAI();
}

void APYAIController::OnPatrolTimerElapsed()
{
    APawn* ControlledPawn = GetPawn();
    if (true == ::IsValid(ControlledPawn))
    {
        UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
        if (true == ::IsValid(NavSystem))
        {
            FNavLocation NextLocation;
            if (true == NavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, PatrolRadius, NextLocation))
            {
                UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, NextLocation.Location);
            }
        }
    }
}
