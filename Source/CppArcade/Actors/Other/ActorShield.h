// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActorShield.generated.h"

class APlayerPawn;

UCLASS()
class CPPARCADE_API AActorShield : public AActor
{
	GENERATED_BODY()

protected:
	FTimerHandle ShieldTimer;
	class APlayerPawn* ShieldForPawn;
	
public:	
	AActorShield();

	UFUNCTION(BlueprintCallable, Category = "Shield")
	void ActivateShield(APlayerPawn* PlayerPawn);

	UFUNCTION(BlueprintCallable, Category = "Shield")
	void DeactivateShield();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Shield")
	float ShieldTime = 5.f;
};
