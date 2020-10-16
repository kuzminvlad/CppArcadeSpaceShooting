// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "./Bonus.h"
#include "BonusHeart.generated.h"

UCLASS()
class CPPARCADE_API ABonusHeart : public ABonus
{
	GENERATED_BODY()

protected:
	virtual void BonusCollected_Implementation() override;	
};
