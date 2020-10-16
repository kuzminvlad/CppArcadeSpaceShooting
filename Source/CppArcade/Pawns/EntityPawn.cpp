// Fill out your copyright notice in the Description page of Project Settings.


#include "EntityPawn.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "../Components/HealthComponent.h"

AEntityPawn::AEntityPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	PawnCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("PawnCollision"));
	PawnCollision->SetCollisionProfileName("Pawn");
	SetRootComponent(PawnCollision);

	PawnMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PawnMesh"));
	PawnMesh->SetupAttachment(RootComponent);

	ShootComponent = CreateDefaultSubobject<UShootComponent>(TEXT("ShootComponent"));
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}

void AEntityPawn::BeginPlay()
{
	Super::BeginPlay();
}

void AEntityPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
