// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "../Components/ShootComponent.h"
#include "EntityPawn.generated.h"

USTRUCT(BlueprintType)
struct FShootInfoLevel
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	TArray<FShootInfo> ShootInfos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	float ShootPeriod;
};

UCLASS()
class CPPARCADE_API AEntityPawn : public APawn
{
	GENERATED_BODY()

public:
	AEntityPawn();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")
	class UBoxComponent* PawnCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")
	class UStaticMeshComponent* PawnMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shooting")
	UShootComponent* ShootComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Shooting")
	TArray<FShootInfoLevel> ShootInfoLevels;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	class UHealthComponent* HealthComponent;
};
