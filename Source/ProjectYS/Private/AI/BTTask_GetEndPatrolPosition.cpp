// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_GetEndPatrolPosition.h"
#include "Controllers/PYAIController.h"
#include "Characters/PYMonMinion.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_GetEndPatrolPosition::UBTTask_GetEndPatrolPosition()
{
	NodeName = TEXT("GetEndPatrolPosition");
}

EBTNodeResult::Type UBTTask_GetEndPatrolPosition::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

    if (EBTNodeResult::Failed == Result)
    {
        return Result;
    }

    APYAIController* AIController = Cast<APYAIController>(OwnerComp.GetAIOwner());
    if (false == ::IsValid(AIController))
    {
        return Result = EBTNodeResult::Failed;
    }

    APYMonMinion* MonMinion = Cast<APYMonMinion>(AIController->GetPawn());
    if (false == ::IsValid(MonMinion))
    {
        return Result = EBTNodeResult::Failed;
    }

    UNavigationSystemV1* NS = UNavigationSystemV1::GetNavigationSystem(MonMinion->GetWorld());
    if (false == ::IsValid(NS))
    {
        return Result = EBTNodeResult::Failed;
    }

    FVector StartPatrolPosition = OwnerComp.GetBlackboardComponent()->GetValueAsVector(APYAIController::StartPatrolPositionKey);
    FNavLocation EndPatrolLocation;
    if (true == NS->GetRandomPointInNavigableRadius(FVector::ZeroVector, AIController->PatrolRadius, EndPatrolLocation))
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsVector(APYAIController::EndPatrolPositionKey, EndPatrolLocation.Location);
        return Result = EBTNodeResult::Succeeded;
    }

    return Result;
}
