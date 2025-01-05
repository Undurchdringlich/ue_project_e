// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "BaseGeometryActor.generated.h"

DECLARE_LOG_CATEGORY_EXTERN( LogBaseGeometry, Log, All )

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

	FGeometryData() : MovementType( EMovementType::Static ), amplitude( 50.0f ), frequency( 2.0f ), Color( FLinearColor::Black ) {}

	UPROPERTY( EditAnywhere, Category = "Movement" )
	EMovementType MovementType;

	UPROPERTY( EditAnywhere, Category = "Movement" )
	float amplitude;

	UPROPERTY( EditAnywhere, Category = "Movement" )
	float frequency;

	UPROPERTY( EditAnywhere, Category = "Design" )
	FLinearColor Color;
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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	FGeometryData GeometryData;

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
	FVector InitLocation;
	void Print();
	void PrintTransform();
	void HandleMovement();
	void SetColor( const FLinearColor& color );
};
