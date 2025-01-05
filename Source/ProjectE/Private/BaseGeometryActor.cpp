// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGeometryActor.h"
#include "Engine/Engine.h"
#include "Materials/MaterialInstanceDynamic.h"

DEFINE_LOG_CATEGORY( LogBaseGeometry )

// Sets default values
ABaseGeometryActor::ABaseGeometryActor() : health( 4 ), damage( 23 ), percents( 56.3465f ), isDead( false )
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>( "BaseMesh");
	SetRootComponent(BaseMesh);
}

// Called when the game starts or when spawned
void ABaseGeometryActor::BeginPlay()
{
	Super::BeginPlay();

	InitLocation = GetActorLocation();
	
	//Print();
	//PrintTransform();

	SetColor( GeometryData.Color );
}

// Called every frame
void ABaseGeometryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	HandleMovement();
}

void ABaseGeometryActor::Print()
{
	UE_LOG( LogTemp, Display, TEXT( "Unreal!" ) );
	UE_LOG( LogTemp, Warning, TEXT( "Unreal!" ) );
	UE_LOG( LogTemp, Error, TEXT( "Unreal!" ) );

	UE_LOG( LogBaseGeometry,
			Display,
			TEXT( "health: %i, percent: %.2f, percentFull: %f, isTest: %i" ),
			health, percents, percents, isDead
	);

	const FString name = "Sara Connor";

	const FString healthStr = "Health = " + FString::FromInt(health);
	const FString percentsStr = "Percents = " + FString::SanitizeFloat( percents );
	const FString isDeadStr = "IsDead = " + FString( isDead ? "true" : "false" );

	const FString stat = FString::Printf( TEXT("%s \n%s \n%s \n%s"), *name, *healthStr, *percentsStr, *isDeadStr );

	// Логируем сообщение в консоли
	UE_LOG( LogBaseGeometry, Warning, TEXT("%s"), *stat);

	// Логируем сообщение на экране
	GEngine->AddOnScreenDebugMessage( -1, 2.0f, FColor::Black, stat );

	GEngine->AddOnScreenDebugMessage( -1, 4.0f, FColor::Red, stat, true, FVector2D( 1.5f, 1.5f ) );
}

void ABaseGeometryActor::PrintTransform()
{
	FTransform transform = GetActorTransform();

	FVector location = transform.GetLocation();
	FRotator rotation = transform.Rotator();
	FVector scale = transform.GetScale3D();

	UE_LOG( LogBaseGeometry, Warning, TEXT( "Actor name: %s" ), *GetActorNameOrLabel() );
	UE_LOG( LogBaseGeometry, Warning, TEXT( "Transform: %s" ), *transform.ToString() );
	UE_LOG( LogBaseGeometry, Warning, TEXT( "Location: %s" ), *location.ToString() );
	UE_LOG( LogBaseGeometry, Warning, TEXT( "Rotation: %s" ), *rotation.ToString() );
	UE_LOG( LogBaseGeometry, Warning, TEXT( "Scale: %s" ), *scale.ToString() );

	UE_LOG( LogBaseGeometry, Error, TEXT( "Human transform: %s" ), *transform.ToHumanReadableString() );
}

void ABaseGeometryActor::HandleMovement()
{
	if( GeometryData.MovementType == EMovementType::Sin )
	{
		// Реализовали движение актора по оси Z
		FVector CurrentLocation = GetActorLocation();
		const float Time = GetWorld()->GetTimeSeconds();
		CurrentLocation.Z = InitLocation.Z + GeometryData.amplitude * FMath::Sin( GeometryData.frequency * Time );

		SetActorLocation( CurrentLocation );
	}
}

void ABaseGeometryActor::SetColor( const FLinearColor& color )
{
	if( UMaterialInstanceDynamic* DynMaterial = BaseMesh->CreateAndSetMaterialInstanceDynamic( 0 ) )
		DynMaterial->SetVectorParameterValue( "Color", color );
}