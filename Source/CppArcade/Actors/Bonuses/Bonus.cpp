// Fill out your copyright notice in the Description page of Project Settings.

#include "Bonus.h"
#include "Kismet/GameplayStatics.h"

ABonus::ABonus()
{
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("BonusCollision"));
	SetRootComponent(Collision);
	Collision->SetCollisionObjectType(ECC_WorldDynamic);
	Collision->SetSphereRadius(50);
}

void ABonus::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float WorldMoveOffset = -300.f * DeltaTime;
	AddActorWorldOffset(FVector(WorldMoveOffset, 0.f, 0.f));
}

void ABonus::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (!OtherActor || !Cast<APlayerPawn>(OtherActor)) return;

	BonusCollected();
}

void ABonus::BonusCollected_Implementation()
{
	if (CollectParticle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), CollectParticle, GetActorTransform(), true);
	}
	Destroy();
}
