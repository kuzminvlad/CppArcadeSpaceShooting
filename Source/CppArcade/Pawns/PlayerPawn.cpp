// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerPawn.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/GameViewportClient.h"
#include "Engine/World.h"
#include "Particles/ParticleSystemComponent.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

APlayerPawn::APlayerPawn()
{
	PawnCollision->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Ignore);
	PawnCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PawnCamera"));
}

void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	PawnMaterial = PawnMesh->GetMaterial(0);
	ShootComponent->ShootInfos = ShootInfoLevels[0].ShootInfos;
	ShootComponent->ShootPeriod = ShootInfoLevels[0].ShootPeriod;
}

void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindTouch(IE_Repeat, this, &APlayerPawn::OnTouchMove);
	InputComponent->BindTouch(IE_Pressed, this, &APlayerPawn::OnTouchPress);
}

void APlayerPawn::OnTouchMove(ETouchIndex::Type FingerIndex, FVector Location)
{
	FVector2D TouchDeltaMove = FVector2D(TouchLocation.X - Location.X, TouchLocation.Y - Location.Y);
	TouchDeltaMove *= TouchMoveSensivity;

	FVector NewLocation = GetActorLocation();
	NewLocation.X += TouchDeltaMove.Y;
	NewLocation.Y -= TouchDeltaMove.X;

	FVector2D NewScreenLocation;
	int32 ScreenSizeX, ScreenSizeY;
	PlayerController->ProjectWorldLocationToScreen(NewLocation, NewScreenLocation);
	PlayerController->GetViewportSize(ScreenSizeX, ScreenSizeY);

	if (NewScreenLocation.X >= 20.f && NewScreenLocation.X <= ScreenSizeX - 20.f &&
		NewScreenLocation.Y >= 20.f && NewScreenLocation.Y <= ScreenSizeY - 30.f)
	{
		SetActorLocation(NewLocation);		
	}

	TouchLocation = FVector2D(Location.X, Location.Y);	
}

void APlayerPawn::OnTouchPress(ETouchIndex::Type FingerIndex, FVector Location)
{
	TouchLocation = FVector2D(Location.X, Location.Y);
}

void APlayerPawn::PossessedBy(AController* NewController)
{
	PlayerController = Cast<APlayerController>(NewController);
}

float APlayerPawn::TakeDamage(float Damage, const FDamageEvent& DamageEvent, AController* InstigatedBy, AActor* DamageCauserr)
{
	if (!CanBeDamaged()) return 0.f;

	Super::TakeDamage(Damage, DamageEvent, InstigatedBy, DamageCauserr);
	PawnDamaged.Broadcast();
	return Damage;
}

bool APlayerPawn::CanBeDamaged_Implementation()
{
	return bCanRecieveDamage;
}

void APlayerPawn::ChangeShootLevel(int Value)
{
	CurrentShootLevel = FMath::Clamp(CurrentShootLevel + Value, 0, ShootInfoLevels.Num() - 1);
	ShootComponent->ShootInfos = ShootInfoLevels[CurrentShootLevel].ShootInfos;
	ShootComponent->ShootPeriod = ShootInfoLevels[CurrentShootLevel].ShootPeriod;
}
