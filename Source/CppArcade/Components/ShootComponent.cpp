// Fill out your copyright notice in the Description page of Project Settings.

#include "ShootComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"

UShootComponent::UShootComponent()
{
}


void UShootComponent::BeginPlay()
{
	Super::BeginPlay();

	StartShooting();
}

void UShootComponent::Shoot()
{
	for (FShootInfo& ShootInfo : ShootInfos)
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = GetOwner();
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		FRotator SpawnRotation = GetOwner()->GetActorRotation();
		SpawnRotation.Add(0.f, ShootInfo.Angle, 0.f);

		FVector SpawnLocation = GetOwner()->GetActorLocation() + SpawnRotation.RotateVector(ShootInfo.Offset);

		AShootProjectile* Projectile = GetWorld()->SpawnActor<AShootProjectile>(ShootInfo.ProjectileClass, SpawnLocation, SpawnRotation, SpawnParameters);
		if (Projectile)
		{
			Projectile->Damage = ShootInfo.Damage;
		}
	}
}

void UShootComponent::StartShooting()
{
	GetWorld()->GetTimerManager().SetTimer(ShootingTimer, this, &UShootComponent::Shoot, ShootPeriod, true, ShootPeriod);
}

void UShootComponent::StopShooting()
{
	GetWorld()->GetTimerManager().ClearTimer(ShootingTimer);
}
