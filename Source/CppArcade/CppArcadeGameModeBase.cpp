// Copyright Epic Games, Inc. All Rights Reserved.

#include "CppArcadeGameModeBase.h"
#include "Components/HealthComponent.h"
#include "Components/EnemySpawnController.h"
#include "Pawns/PlayerPawn.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

ACppArcadeGameModeBase::ACppArcadeGameModeBase()
{
	EnemySpawnController = CreateDefaultSubobject<UEnemySpawnController>(TEXT("EnemySpawnController"));
}

void ACppArcadeGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	PlayerPawn = Cast<APlayerPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (!PlayerPawn) return;

	PlayerPawn->HealthComponent->OnHealthEnded.AddDynamic(this, &ACppArcadeGameModeBase::EndGame);
	GetWorld()->GetTimerManager().SetTimer(IncreaseDifficultyTimer, this, &ACppArcadeGameModeBase::IncreaseDifficulty, IncreaseDifficultyPeriod, true);
}

void ACppArcadeGameModeBase::EndGame()
{
	bIsGameOver = true;
	EnemySpawnController->SetActive(false);
	GameOver.Broadcast();
	UGameplayStatics::GetPlayerPawn(this, 0)->Destroy();
	SetPause(UGameplayStatics::GetPlayerController(this, 0));
}

void ACppArcadeGameModeBase::AddPoints(int Points)
{
	GamePoints += Points;
}

void ACppArcadeGameModeBase::IncreaseDifficulty()
{
	EnemySpawnController->ChangeStageTimeMultiplier = FMath::Max(EnemySpawnController->ChangeStageTimeMultiplier * 0.95f, 0.4f);
}
