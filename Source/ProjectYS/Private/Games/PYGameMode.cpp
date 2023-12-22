// Fill out your copyright notice in the Description page of Project Settings.


#include "Games/PYGameMode.h"
#include "Controllers/PYPlayerController.h"

APYGameMode::APYGameMode()
{
	PlayerControllerClass = APYPlayerController::StaticClass();
}
