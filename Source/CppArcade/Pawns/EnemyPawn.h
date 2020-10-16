// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "./EntityPawn.h"
#include "../Actors/Bonuses/Bonus.h"
#include "EnemyPawn.generated.h"

USTRUCT(BlueprintType)
struct FBonusChance
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bonus")
	TSubclassOf<ABonus> BonusClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bonus")
	float Chance;
};

UCLASS()
class CPPARCADE_API AEnemyPawn : public AEntityPawn
{
	GENERATED_BODY()

public:
	AEnemyPawn();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void KillPawn();

	UFUNCTION()
	void OnEnemyOverlap(AActor* OverlapedActor, AActor* OtherActor);

	void SpawnBonuses();

	FRandomStream Random;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Pawn")
	void DestroyPawn();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pawn")
	int DestroyPoints;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Bonus")
	TArray<FBonusChance> PossibleBonuses;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visual")
	UParticleSystem* DestroyParticle;
};
