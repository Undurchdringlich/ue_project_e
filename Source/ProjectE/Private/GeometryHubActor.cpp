// Fill out your copyright notice in the Description page of Project Settings.


#include "GeometryHubActor.h"
#include "Engine/World.h"

DEFINE_LOG_CATEGORY( LogGeometryHub )

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
		//for( uint32 i = 0; i < 10; i++ )
		//{
		//	const FTransform SpawnTransform( FRotator::ZeroRotator, FVector( 0.0f, 100.0f * i, 1000.0f ) );
		//	if( ABaseGeometryActor* SpawnActor = World->SpawnActor<ABaseGeometryActor>( GeometryClass, SpawnTransform ) )
		//	{
		//		FGeometryData GeometryData;
		//		GeometryData.MovementType = FMath::RandBool() ?  EMovementType::Sin : EMovementType::Static;
		//		GeometryData.TimerRate = i;
		//		SpawnActor->SetGeometryData( GeometryData );
		//	}
		//}

		//// BeginPlay вызываем вручную методом FinishSpawning
		//for( uint32 i = 0; i < 10; i++ )
		//{
		//	const FTransform SpawnTransform( FRotator::ZeroRotator, FVector( 0.0f, 100.0f * i, 2000.0f ) );
		//	if( ABaseGeometryActor* SpawnActor = World->SpawnActorDeferred<ABaseGeometryActor>( GeometryClass, SpawnTransform ) )
		//	{
		//		FGeometryData GeometryData;
		//		GeometryData.Color = FLinearColor::MakeRandomColor();

		//		GeometryData.MovementType = FMath::RandBool() ? EMovementType::Sin : EMovementType::Static;
		//		GeometryData.TimerRate = i;
		//		SpawnActor->SetGeometryData( GeometryData );
		//		SpawnActor->FinishSpawning( SpawnTransform );
		//	}
		//}

		// Спавн объектов, установленных в эдиторе
		for( const auto& Payload : GeometryPayloads )
		{
			if( Payload.GeometryClass )
			{
				if( ABaseGeometryActor* SpawnActor = World->SpawnActorDeferred<ABaseGeometryActor>( Payload.GeometryClass, Payload.InitialTransform ) )
				{
					SpawnActor->SetGeometryData( Payload.Data );
					SpawnActor->OnColorChanged.AddDynamic( this, &AGeometryHubActor::OnColorChanged );
					SpawnActor->OnTimerFinished.AddUObject( this, &AGeometryHubActor::OnTimerFinished );
					SpawnActor->FinishSpawning( Payload.InitialTransform );
				}
			}
		}
	}
}

void AGeometryHubActor::OnColorChanged( const FLinearColor& Color, const FString& Name )
{
	UE_LOG( LogGeometryHub, Warning, TEXT("Actor name: %s, Color: %s"), *Name, *Color.ToString() );
}

void AGeometryHubActor::OnTimerFinished( AActor * Actor )
{
	if( !Actor )
		return;
	UE_LOG( LogGeometryHub, Error, TEXT( "Timer finished: %s" ), *Actor->GetName() );

	ABaseGeometryActor* Geometry = Cast<ABaseGeometryActor>( Actor );
	if( !Geometry )
		return;
	UE_LOG( LogGeometryHub, Display, TEXT( "Cast is success, amplitude: %f" ), Geometry->GetGeometryData().amplitude);

	Geometry->Destroy();
	//Geometry->SetLifeSpan( 2.0f );
}

