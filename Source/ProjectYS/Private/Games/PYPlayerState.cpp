// Fill out your copyright notice in the Description page of Project Settings.


#include "Games/PYPlayerState.h"

APYPlayerState::APYPlayerState()
{
}

void APYPlayerState::InitPlayerState()
{
	CurrentMode = PlayerMode::MODE_HAND;
}

void APYPlayerState::SetPlayerMode(PlayerMode Mode)
{
    PlayerMode OldPlayerMode = CurrentMode;
    CurrentMode = Mode;
    OnCurrentModeChangedDelegate.Broadcast(OldPlayerMode, CurrentMode);
}

void APYPlayerState::SetPlayerSword(APYWeapon* Sword)
{
    CurrentSword = Sword;
}

void APYPlayerState::SetPlayerGun(APYWeapon* Gun)
{
    CurrentGun = Gun;
}
