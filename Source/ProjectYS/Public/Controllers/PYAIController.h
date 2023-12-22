// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PYAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTYS_API APYAIController : public AAIController
{
	GENERATED_BODY()
	
public:
    APYAIController();

public:
    void BeginAI(APawn* InPawn);

    void EndAI();

protected:
    virtual void BeginPlay() override;

    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
    void OnPatrolTimerElapsed();

public:
    static const float PatrolRadius;

    static const FName StartPatrolPositionKey;

    static const FName EndPatrolPositionKey;

    static const FName TargetActorKey;

private:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = APYAIController, meta = (AllowPrivateAccess))
    TObjectPtr<class UBlackboardData> BlackboardDataAsset;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = APYAIController, meta = (AllowPrivateAccess))
    TObjectPtr<class UBehaviorTree> BehaviorTree;
};
