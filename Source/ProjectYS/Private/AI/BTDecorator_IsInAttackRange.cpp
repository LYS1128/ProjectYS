// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTDecorator_IsInAttackRange.h"
#include "Controllers/PYAIController.h"
#include "Characters/PYMonMinion.h"
#include "Characters/PYCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

const float UBTDecorator_IsInAttackRange::AttackRange(200.f);

UBTDecorator_IsInAttackRange::UBTDecorator_IsInAttackRange()
{
	NodeName = TEXT("IsInAttackRange");
}

bool UBTDecorator_IsInAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

    APYAIController* AIC = Cast<APYAIController>(OwnerComp.GetAIOwner());
    if (true == ::IsValid(AIC))
    {
        APYMonMinion* NPC = Cast<APYMonMinion>(AIC->GetPawn());
        if (true == ::IsValid(NPC))
        {
            APYCharacter* TargetPlayerCharacter = Cast<APYCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(APYAIController::TargetActorKey));
            if (true == ::IsValid(TargetPlayerCharacter))
            {
                bResult = (NPC->GetDistanceTo(TargetPlayerCharacter) <= AttackRange); //몬스터 근접 콤보
                NPC->SetPlayerDetect(bResult);
                return bResult;
            }
        }
    }

    return bResult = false;
}
