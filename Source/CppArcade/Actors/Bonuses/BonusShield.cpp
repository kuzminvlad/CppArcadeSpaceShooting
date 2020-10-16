// Fill out your copyright notice in the Description page of Project Settings.

#include "BonusShield.h"
#include "Kismet/GameplayStatics.h"
#include "../../Pawns/PlayerPawn.h"
#include "Engine/World.h"
#include "../Other/ActorShield.h"

void ABonusShield::BonusCollected_Implementation()
{
	APawn* Pawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if (!Pawn) return;
	APlayerPawn* PlayerPawn = Cast<APlayerPawn>(Pawn);
	if (!PlayerPawn || !PlayerPawn->bCanRecieveDamage) return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AActorShield* Shield = GetWorld()->SpawnActor<AActorShield>(ShieldClass, SpawnParams);
	if (Shield)	Shield->ActivateShield(PlayerPawn);

	Super::BonusCollected_Implementation();
}
