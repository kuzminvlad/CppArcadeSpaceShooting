// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Actors/Projectiles/ShootProjectile.h"
#include "ShootComponent.generated.h"

USTRUCT(BlueprintType)
struct FShootInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	TSubclassOf<AShootProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	FVector Offset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	float Angle;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPPARCADE_API UShootComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	void Shoot();

	FTimerHandle ShootingTimer;

public:
	UShootComponent();

	UFUNCTION(BlueprintCallable, Category = "Shooting")
	void StartShooting();

	UFUNCTION(BlueprintCallable, Category = "Shooting")
	void StopShooting();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shooting")
	float ShootPeriod = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shooting")
	TArray<FShootInfo> ShootInfos;
};
