// Fill out your copyright notice in the Description page of Project Settings.


#include "GeometryHubActor.h"
#include "Engine/World.h"

// Sets default values
AGeometryHubActor::AGeometryHubActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGeometryHubActor::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnActors();
}

// Called every frame
void AGeometryHubActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGeometryHubActor::SpawnActors()
{
	if( UWorld* World = GetWorld() )
	{
		// BeginPlay вызвался сразу после спавна
		for( uint32 i = 0; i < 10; i++ )
		{
			const FTransform SpawnTransform( FRotator::ZeroRotator, FVector( 0.0f, 100.0f * i, 1000.0f ) );
			if( ABaseGeometryActor* SpawnActor = World->SpawnActor<ABaseGeometryActor>( GeometryClass, SpawnTransform ) )
			{
				FGeometryData GeometryData;
				GeometryData.MovementType = FMath::RandBool() ?  EMovementType::Sin : EMovementType::Static;
				GeometryData.TimerRate = i;
				SpawnActor->SetGeometryData( GeometryData );
			}
		}

		// BeginPlay вызываем вручную методом FinishSpawning
		for( uint32 i = 0; i < 10; i++ )
		{
			const FTransform SpawnTransform( FRotator::ZeroRotator, FVector( 0.0f, 100.0f * i, 2000.0f ) );
			if( ABaseGeometryActor* SpawnActor = World->SpawnActorDeferred<ABaseGeometryActor>( GeometryClass, SpawnTransform ) )
			{
				FGeometryData GeometryData;
				GeometryData.Color = FLinearColor::MakeRandomColor();

				GeometryData.MovementType = FMath::RandBool() ? EMovementType::Sin : EMovementType::Static;
				GeometryData.TimerRate = i;
				SpawnActor->SetGeometryData( GeometryData );
				SpawnActor->FinishSpawning( SpawnTransform );
			}
		}

		// Спавн объектов, установленных в эдиторе
		for( const auto& Payload : GeometryPayloads )
		{
			if( Payload.GeometryClass )
			{
				if( ABaseGeometryActor* SpawnActor = World->SpawnActorDeferred<ABaseGeometryActor>( Payload.GeometryClass, Payload.InitialTransform ) )
				{
					SpawnActor->SetGeometryData( Payload.Data );
					SpawnActor->FinishSpawning( Payload.InitialTransform );
				}
			}
			
		}
	}
}

