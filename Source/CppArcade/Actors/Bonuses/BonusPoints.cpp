// Fill out your copyright notice in the Description page of Project Settings.

#include "BonusPoints.h"
#include "Kismet/GameplayStatics.h"
#include "../../CppArcadeGameModeBase.h"

void ABonusPoints::BonusCollected_Implementation()
{
	ACppArcadeGameModeBase* Gamemode = Cast< ACppArcadeGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (Gamemode) Gamemode->AddPoints(Points);

	Super::BonusCollected_Implementation();
}

