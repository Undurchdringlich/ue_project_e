// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SandBoxPlayerController.generated.h"

DECLARE_LOG_CATEGORY_EXTERN( LogSandBoxPlayerController, All, All )


UCLASS()
class PROJECTE_API ASandBoxPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;

private:
	void ChangePawn();

	UPROPERTY()
	TArray<AActor*> Pawns;
};
