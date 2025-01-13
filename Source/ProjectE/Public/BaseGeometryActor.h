// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "BaseGeometryActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FOnColorChanged, const FLinearColor&, Color, const FString&, Name );
DECLARE_MULTICAST_DELEGATE_OneParam( FOnTimerFinished, AActor* );

DECLARE_LOG_CATEGORY_EXTERN( LogBaseGeometry, All, All )

UENUM(BlueprintType)
enum class EMovementType : uint8
{
	Sin,
	Static
};

USTRUCT(BlueprintType)
struct FGeometryData
{
	GENERATED_USTRUCT_BODY()

	FGeometryData() : MovementType( EMovementType::Static ), amplitude( 50.0f ), frequency( 2.0f ), Color( FLinearColor::Black ), TimerRate( 3.0f ) {}

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Movement" )
	EMovementType MovementType;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Movement" )
	float amplitude;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Movement" )
	float frequency;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Design" )
	FLinearColor Color;

	UPROPERTY( EditAnywhere, Category = "Design" )
	float TimerRate;
};

UCLASS()
class PROJECTE_API ABaseGeometryActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseGeometryActor();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

	void UpdateTimerRate( const float NewTimerRate );

	void SetGeometryData( const FGeometryData& NewGeometryData );

	UFUNCTION(BlueprintCallable)
	FGeometryData GetGeometryData() const;
	
	UPROPERTY(BlueprintAssignable)
	FOnColorChanged OnColorChanged;

	FOnTimerFinished OnTimerFinished;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason ) override;

	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	FGeometryData GeometryData;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Stats" )
	int32 health;

	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite )
	int32 damage;

	UPROPERTY( EditInstanceOnly, BlueprintReadWrite )
	float percents;

	UPROPERTY( VisibleAnywhere, BlueprintReadWrite )
	bool isDead;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	FVector InitLocation;
	FTimerHandle TimerHandle;

	uint32 TimerCount = 0;
	uint32 MaxTimerCount = 5;

	void Print();
	void PrintTransform();
	void HandleMovement();
	void SetColor( const FLinearColor& color );

	void OnTimerFire();
};
