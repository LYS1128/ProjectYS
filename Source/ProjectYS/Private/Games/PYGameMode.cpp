// Fill out your copyright notice in the Description page of Project Settings.


#include "Games/PYGameMode.h"
#include "Controllers/PYPlayerController.h"
#include "Games/PYPlayerState.h"

APYGameMode::APYGameMode()
{
	PlayerControllerClass = APYPlayerController::StaticClass();
}

void APYGameMode::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);

    APYPlayerState* PlayerState = NewPlayer->GetPlayerState<APYPlayerState>();
    if (true == ::IsValid(PlayerState))
    {
        PlayerState->InitPlayerState();
    }
}
