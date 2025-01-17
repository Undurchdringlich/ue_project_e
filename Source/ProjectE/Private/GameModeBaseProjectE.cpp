// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModeBaseProjectE.h"
#include "SandboxPawn.h"
#include "SandBoxPlayerController.h"

AGameModeBaseProjectE::AGameModeBaseProjectE()
{
    DefaultPawnClass = ASandboxPawn::StaticClass();
    PlayerControllerClass = ASandBoxPlayerController::StaticClass();
}
