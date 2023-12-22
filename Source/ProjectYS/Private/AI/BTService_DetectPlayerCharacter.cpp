// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_DetectPlayerCharacter.h"
#include "Controllers/PYAIController.h"
#include "Characters/PYMonMinion.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Characters/PYPlayer.h"

UBTService_DetectPlayerCharacter::UBTService_DetectPlayerCharacter()
{
	NodeName = TEXT("DetectPlayerCharacter");
	Interval = 1.f;
}

void UBTService_DetectPlayerCharacter::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    APYAIController* AIC = Cast<APYAIController>(OwnerComp.GetAIOwner());
    if (true == ::IsValid(AIC))
    {
        APYMonMinion* MonMinion = Cast<APYMonMinion>(AIC->GetPawn());
        if (true == ::IsValid(MonMinion))
        {
            UWorld* World = MonMinion->GetWorld();
            if (true == ::IsValid(World))
            {
                FVector CenterPosition = MonMinion->GetActorLocation();
                float DetectRadius = 300.f;
                TArray<FOverlapResult> OverlapResults;
                FCollisionQueryParams CollisionQueryParams(NAME_None, false, MonMinion);
                bool bResult = World->OverlapMultiByChannel(
                    OverlapResults,
                    CenterPosition,
                    FQuat::Identity,
                    ECollisionChannel::ECC_GameTraceChannel2,
                    FCollisionShape::MakeSphere(DetectRadius),
                    CollisionQueryParams
                );

                if (true == bResult)
                {
                    for (auto const& OverlapResult : OverlapResults)
                    {
                        APYPlayer* PC = Cast<APYPlayer>(OverlapResult.GetActor());
                        if (true == ::IsValid(PC))
                        {
                            if (true == PC->GetController()->IsPlayerController())
                            {
                                //MonMinion->SetPlayerDetect(true); //몬스터 근접 콤보
                                OwnerComp.GetBlackboardComponent()->SetValueAsObject(APYAIController::TargetActorKey, PC);

                                UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("Detected!")));
                                DrawDebugSphere(World, CenterPosition, DetectRadius, 16, FColor::Red, false, 0.5f);
                                DrawDebugPoint(World, PC->GetActorLocation(), 10.f, FColor::Red, false, 0.5f);
                                DrawDebugLine(World, MonMinion->GetActorLocation(), PC->GetActorLocation(), FColor::Red, false, 0.5f, 0u, 3.f);

                                return;
                            }
                            else
                            {                               
                                OwnerComp.GetBlackboardComponent()->SetValueAsObject(APYAIController::TargetActorKey, nullptr);

                                DrawDebugSphere(World, CenterPosition, DetectRadius, 16, FColor::Green, false, 0.5f);
                            }
                        }
                    }
                }
                else
                {
                    OwnerComp.GetBlackboardComponent()->SetValueAsObject(APYAIController::TargetActorKey, nullptr);
                }

                MonMinion->SetPlayerDetect(false); //몬스터 근접 콤보
                UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("No target detected...")));

                DrawDebugSphere(World, CenterPosition, DetectRadius, 16, FColor::Green, false, 0.5f);
            }
        }
    }
}
