// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "../Pawns/EnemyPawn.h"
#include "EnemySpawnController.generated.h"

USTRUCT(BlueprintType)
struct FEnemySpawnInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
	TSubclassOf<AEnemyPawn> EnemyClass = AEnemyPawn::StaticClass();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
	FTransform SpawnTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
	int NumOfEnemies;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
	float SpawnDelay;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPPARCADE_API UEnemySpawnController : public UActorComponent
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	void StartSpawnStage();
	void SpawnEnemy();
	virtual void Deactivate() override;

	FEnemySpawnInfo SpawnStage;
	int EnemiesSpawned = 0;

	FTimerHandle ChangeStateTimer;
	FTimerHandle EnemySpawnTimer;
	FRandomStream Random;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemies")
	TArray<FEnemySpawnInfo> SpawnStages;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemies")
	float StageMinDelay;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemies")
	float StageMaxDelay;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemies")
	float ChangeStageTimeMultiplier = 2.f;
};
