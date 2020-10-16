// Fill out your copyright notice in the Description page of Project Settings.

#include "ActorShield.h"
#include "../../Pawns/PlayerPawn.h"
#include "Engine/World.h"
#include "TimerManager.h"

AActorShield::AActorShield()
{
}

void AActorShield::ActivateShield(APlayerPawn* PlayerPawn)
{
	if (!PlayerPawn)
	{
		Destroy();
		return;
	}

	ShieldForPawn = PlayerPawn;
	PlayerPawn->bCanRecieveDamage = false;

	FAttachmentTransformRules AttachRules = FAttachmentTransformRules(
		EAttachmentRule::SnapToTarget,
		EAttachmentRule::SnapToTarget,
		EAttachmentRule::KeepWorld,
		false
	);
	AttachToActor(PlayerPawn, AttachRules);

	GetWorld()->GetTimerManager().SetTimer(ShieldTimer, this, &AActorShield::DeactivateShield, ShieldTime, false);
}

void AActorShield::DeactivateShield()
{
	if (!ShieldForPawn) return;

	ShieldForPawn->bCanRecieveDamage = true;
	Destroy();
}
