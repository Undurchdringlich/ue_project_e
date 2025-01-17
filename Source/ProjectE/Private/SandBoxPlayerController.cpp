// Fill out your copyright notice in the Description page of Project Settings.


#include "SandBoxPlayerController.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SandboxPawn.h"

DEFINE_LOG_CATEGORY( LogSandBoxPlayerController )

void ASandBoxPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if( !InputComponent )
        return;

    InputComponent->BindAction( "ChangePawn", IE_Pressed, this, &ASandBoxPlayerController::ChangePawn );
}

void ASandBoxPlayerController::BeginPlay()
{
    Super::BeginPlay();

    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASandboxPawn::StaticClass(), Pawns);
}

void ASandBoxPlayerController::ChangePawn()
{
    for( AActor* CurrentPawn : Pawns )
    {
        if( CurrentPawn && CurrentPawn != GetPawnOrSpectator() )
        {
            ASandboxPawn* CurrentSandboxPawn = Cast<ASandboxPawn>( CurrentPawn );
            if( CurrentSandboxPawn )
            {
                UE_LOG( LogSandBoxPlayerController, Error, TEXT( "Change player pawn" ) );
                Possess( CurrentSandboxPawn );
                break;
            }
        }
    }
}
