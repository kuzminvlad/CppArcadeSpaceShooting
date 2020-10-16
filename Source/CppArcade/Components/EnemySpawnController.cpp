// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemySpawnController.h"

void UEnemySpawnController::BeginPlay()
{
	Super::BeginPlay();

	Random.GenerateNewSeed();
	StartSpawnStage();
}

void UEnemySpawnController::StartSpawnStage()
{
	SpawnStage = SpawnStages[Random.RandRange(0, SpawnStages.Num() - 1)];

	EnemiesSpawned = 0;
	SpawnEnemy();

	float ChangeStateTime = Random.FRandRange(StageMinDelay, StageMaxDelay) * ChangeStageTimeMultiplier;
	GetWorld()->GetTimerManager().SetTimer(ChangeStateTimer, this, &UEnemySpawnController::StartSpawnStage, ChangeStateTime, false);
}

void UEnemySpawnController::SpawnEnemy()
{
	FActorSpawnParameters SpawnParameters;
	GetWorld()->SpawnActor<AEnemyPawn>(SpawnStage.EnemyClass, SpawnStage.SpawnTransform, SpawnParameters);

	EnemiesSpawned++;
	if (EnemiesSpawned < SpawnStage.NumOfEnemies)
	{
		GetWorld()->GetTimerManager().SetTimer(EnemySpawnTimer, this, &UEnemySpawnController::SpawnEnemy, SpawnStage.SpawnDelay, false);
	}
}

void UEnemySpawnController::Deactivate()
{
	Super::Deactivate();

	GetWorld()->GetTimerManager().ClearTimer(ChangeStateTimer);
	GetWorld()->GetTimerManager().ClearTimer(EnemySpawnTimer);
}
