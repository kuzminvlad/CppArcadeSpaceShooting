// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyPawn.h"
#include "Components/StaticMeshComponent.h"
#include "../Components/HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "../CppArcadeGameModeBase.h"

AEnemyPawn::AEnemyPawn()
{
	PawnMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AEnemyPawn::BeginPlay()
{
	Super::BeginPlay();

	Random.GenerateNewSeed();	
	HealthComponent->OnHealthEnded.AddDynamic(this, &AEnemyPawn::KillPawn);
	OnActorBeginOverlap.AddDynamic(this, &AEnemyPawn::OnEnemyOverlap);
}

void AEnemyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float WorldMoveOffset = -300.f * DeltaTime;
	AddActorWorldOffset(FVector(WorldMoveOffset, 0.f, 0.f));
}


void AEnemyPawn::OnEnemyOverlap(AActor* OverlapedActor, AActor* OtherActor)
{
	if (OtherActor != UGameplayStatics::GetPlayerPawn(this, 0))	return;

	float AppliedDamage = UGameplayStatics::ApplyDamage(OtherActor, 100.f, GetController(), this, UDamageType::StaticClass());
	if (AppliedDamage > 0.f) DestroyPawn();
}

void AEnemyPawn::SpawnBonuses()
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	for (auto& Bonus : PossibleBonuses)
	{
		if (Random.RandRange(0, 100) <= Bonus.Chance)
		{
			GetWorld()->SpawnActor<ABonus>(Bonus.BonusClass, GetActorLocation(), FRotator(0.f), SpawnParameters);
			break;
		}
	}
}

void AEnemyPawn::DestroyPawn()
{
	if (DestroyParticle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DestroyParticle, GetActorTransform(), true);
	}
	Destroy();
}

void AEnemyPawn::KillPawn()
{
	ACppArcadeGameModeBase* Gamemode = Cast< ACppArcadeGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (Gamemode) Gamemode->AddPoints(DestroyPoints);

	SpawnBonuses();
	DestroyPawn();
}
