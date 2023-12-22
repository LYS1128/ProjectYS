// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_Attack.h"
#include "Controllers/PYAIController.h"
#include "Characters/PYMonMinion.h"

UBTTask_Attack::UBTTask_Attack()
{
	bNotifyTick = true;
}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

    APYAIController* AIC = Cast<APYAIController>(OwnerComp.GetAIOwner());
    if (true == ::IsValid(AIC))
    {
        APYMonMinion* NPC = Cast<APYMonMinion>(AIC->GetPawn());
        if (true == ::IsValid(NPC))
        {
            if (false == NPC->IsNowAttacking())
            {
                FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
            }
        }
    }
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

    APYAIController* AIC = Cast<APYAIController>(OwnerComp.GetAIOwner());
    if (true == ::IsValid(AIC))
    {
        APYMonMinion* NPC = Cast<APYMonMinion>(AIC->GetPawn());
        if (true == ::IsValid(NPC))
        {
            NPC->Attack();
        }
    }

    return EBTNodeResult::InProgress;
}
