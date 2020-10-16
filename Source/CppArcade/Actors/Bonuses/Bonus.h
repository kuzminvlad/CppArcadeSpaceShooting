// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "../../Pawns/PlayerPawn.h"
#include "Bonus.generated.h"

UCLASS(Blueprintable)
class CPPARCADE_API ABonus : public AActor
{
	GENERATED_BODY()

protected:
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	UFUNCTION(BlueprintNativeEvent)
	void BonusCollected();
	virtual void BonusCollected_Implementation();

public:
	ABonus();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bonus")
	USphereComponent* Collision;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visual")
	UParticleSystem* CollectParticle;
};
