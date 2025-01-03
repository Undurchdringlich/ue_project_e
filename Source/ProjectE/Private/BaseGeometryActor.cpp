// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGeometryActor.h"
#include "Engine/Engine.h"

DEFINE_LOG_CATEGORY( LogBaseGeometry )

// Sets default values
ABaseGeometryActor::ABaseGeometryActor() : amplitude( 50.0f ), frequency( 2.0f ), health( 4 ), damage( 23 ), percents( 56.3465f ), isDead( false )
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	baseMesh = CreateDefaultSubobject<UStaticMeshComponent>( "BaseMesh");
	SetRootComponent(baseMesh);
}

// Called when the game starts or when spawned
void ABaseGeometryActor::BeginPlay()
{
	Super::BeginPlay();

	InitLocation = GetActorLocation();
	
	//Print();
	PrintTransform();
}

// Called every frame
void ABaseGeometryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ����������� �������� ������ �� ��� Z
	FVector current_location = GetActorLocation();
	float time = GetWorld()->GetTimeSeconds();
	current_location.Z = InitLocation.Z + amplitude * FMath::Sin( frequency * time );

	SetActorLocation( current_location );
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

	// �������� ��������� � �������
	UE_LOG( LogBaseGeometry, Warning, TEXT("%s"), *stat);

	// �������� ��������� �� ������
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
