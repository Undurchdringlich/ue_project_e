// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGeometryActor.h"

// Sets default values
ABaseGeometryActor::ABaseGeometryActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseGeometryActor::BeginPlay()
{
	Super::BeginPlay();
	
	Print();
}

// Called every frame
void ABaseGeometryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseGeometryActor::Print()
{
	UE_LOG( LogTemp, Display, TEXT( "Unreal!" ) );
	UE_LOG( LogTemp, Warning, TEXT( "Unreal!" ) );
	UE_LOG( LogTemp, Error, TEXT( "Unreal!" ) );

	int intTest = 4;
	float percents = 56.3465;
	bool isTest = true;

	UE_LOG( LogTemp,
			Display,
			TEXT( "intTest: %i, percent: %.2f, percentFull: %f, isTest: %i" ),
			intTest, percents, percents, isTest
	);
}

