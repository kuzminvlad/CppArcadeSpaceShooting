// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CppArcadeGameModeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameOverEvent);

UCLASS()
class CPPARCADE_API ACppArcadeGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	bool bIsGameOver;
	FTimerHandle IncreaseDifficultyTimer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemies");
	class UEnemySpawnController* EnemySpawnController;

	UPROPERTY(BlueprintAssignable, Category = "Game")
	FGameOverEvent GameOver;

	UPROPERTY(BlueprintReadWrite, Category = "Game")
	float PlayerRecoverTime = 3.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
	float IncreaseDifficultyPeriod = 5.f;

	UPROPERTY(BlueprintReadOnly, Category = "Game")
	class APlayerPawn* PlayerPawn;
public:
	ACppArcadeGameModeBase();

	UFUNCTION(BlueprintCallable, Category = "Game")
	void IncreaseDifficulty();

	UFUNCTION(BlueprintCallable, Category = "Game")
	void EndGame();

	UFUNCTION(BlueprintCallable, Category = "Game")
	void AddPoints(int Points);

	UPROPERTY(BlueprintReadOnly, Category = "Game")
	int GamePoints;
};
