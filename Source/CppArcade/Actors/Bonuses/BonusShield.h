// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "./Bonus.h"
#include "BonusShield.generated.h"

class AActorShield;

UCLASS()
class CPPARCADE_API ABonusShield : public ABonus
{
	GENERATED_BODY()

protected:
	virtual void BonusCollected_Implementation() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shield")
	TSubclassOf<AActorShield> ShieldClass;
};
