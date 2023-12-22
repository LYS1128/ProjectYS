// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_TurnToTarget.h"
#include "Controllers/PYAIController.h"
#include "Characters/PYMonMinion.h"
#include "Characters/PYCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_TurnToTarget::UBTTask_TurnToTarget()
{
	NodeName = TEXT("TurnToTargetActor");
}

EBTNodeResult::Type UBTTask_TurnToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

    APYAIController* AIC = Cast<APYAIController>(OwnerComp.GetAIOwner());
    if (true == ::IsValid(AIC))
    {
        APYMonMinion* NPC = Cast<APYMonMinion>(AIC->GetPawn());
        if (true == ::IsValid(NPC))
        {
            if (APYCharacter* TargetPC = Cast<APYCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AIC->TargetActorKey)))
            {
                FVector LookVector = TargetPC->GetActorLocation() - NPC->GetActorLocation();
                LookVector.Z = 0.f;
                FRotator TargetRotation = FRotationMatrix::MakeFromX(LookVector).Rotator();
                NPC->SetActorRotation(FMath::RInterpTo(NPC->GetActorRotation(), TargetRotation, GetWorld()->GetDeltaSeconds(), 2.f));

                return Result = EBTNodeResult::Succeeded;
            }
        }
    }

    return Result = EBTNodeResult::Failed;
}
