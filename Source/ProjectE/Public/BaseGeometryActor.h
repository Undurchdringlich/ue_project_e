// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseGeometryActor.generated.h"

DECLARE_LOG_CATEGORY_EXTERN( LogBaseGeometry, Log, All )

UCLASS()
class PROJECTE_API ABaseGeometryActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseGeometryActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Stats")
	int32 health;

	UPROPERTY(EditDefaultsOnly)
	int32 damage;

	UPROPERTY(EditInstanceOnly)
	float percents;

	UPROPERTY(VisibleAnywhere)
	bool isDead;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void Print();

};
