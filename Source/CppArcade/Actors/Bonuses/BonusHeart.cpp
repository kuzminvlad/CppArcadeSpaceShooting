// Fill out your copyright notice in the Description page of Project Settings.

#include "BonusHeart.h"
#include "../../Pawns/PlayerPawn.h"
#include "../../Components/HealthComponent.h"

void ABonusHeart::BonusCollected_Implementation()
{
	APawn* Pawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if (!Pawn) return;
	APlayerPawn* PlayerPawn = Cast<APlayerPawn>(Pawn);
	if (!PlayerPawn) return;

	PlayerPawn->HealthComponent->ChangeHealth(25.f);

	Super::BonusCollected_Implementation();
}

