// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include <BaseGeometryActor.h>

#include "GeometryHubActor.generated.h"

DECLARE_LOG_CATEGORY_EXTERN( LogGeometryHub, All, All )

USTRUCT( BlueprintType )
struct FGeometryPayload
{  
	GENERATED_USTRUCT_BODY()

	UPROPERTY( EditAnywhere )
	TSubclassOf<ABaseGeometryActor> GeometryClass;

	UPROPERTY( EditAnywhere )
	FGeometryData Data;

	UPROPERTY( EditAnywhere )
	FTransform InitialTransform;
};

UCLASS()
class PROJECTE_API AGeometryHubActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGeometryHubActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY( EditAnywhere )
	TArray<FGeometryPayload> GeometryPayloads;

	// Только указанный класс или производный от него
	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseGeometryActor> GeometryClass;

	// Любой класс
	UPROPERTY( EditAnywhere )
	UClass* Class;

	// Объект, заспавненный в игровом мире указанного класса
	UPROPERTY( EditAnywhere )
	ABaseGeometryActor* GeometryObject;

	void SpawnActors();

	UFUNCTION()
	void OnColorChanged( const FLinearColor& color, const FString& Name );


	void OnTimerFinished( AActor* Actor );

};
