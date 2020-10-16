// Fill out your copyright notice in the Description page of Project Settings.

#include "BonusShootLevelUp.h"
#include "Kismet/GameplayStatics.h"
#include "../../Pawns/PlayerPawn.h"

void ABonusShootLevelUp::BonusCollected_Implementation()
{
	APlayerPawn* PlayerPawn = Cast<APlayerPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (!PlayerPawn) return;

	PlayerPawn->ChangeShootLevel(1);

	Super::BonusCollected_Implementation();
}
