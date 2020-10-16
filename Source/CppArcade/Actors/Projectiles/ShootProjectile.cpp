// Fill out your copyright notice in the Description page of Project Settings.

#include "ShootProjectile.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

AShootProjectile::AShootProjectile() : ProjectileSpeed(1000.f)
{
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("ProjectileCollision"));
	SetRootComponent(Collision);
	Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collision);
	Mesh->SetCollisionProfileName("NoCollision");
}

void AShootProjectile::BeginPlay()
{
	Super::BeginPlay();
	if (GetOwner())
	{
		Collision->IgnoreActorWhenMoving(GetOwner(), true);
		UBoxComponent* OwnerCollision = GetOwner()->FindComponentByClass<UBoxComponent>();
		OwnerCollision->IgnoreActorWhenMoving(this, true);
		Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
	Collision->OnComponentBeginOverlap.AddDynamic(this, &AShootProjectile::OnProjectileOverlap);
}

void AShootProjectile::OnProjectileOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 BodyIndex, bool Sweep, const FHitResult& Hit)
{
	if (!OtherActor || !Cast<APawn>(OtherActor)) return; //If no overlapped actor or it is not pawn
	if (!GetOwner()) return;
	APawn* PawnOwner = Cast<APawn>(GetOwner());
	if (!PawnOwner) return;

	AController* PawnInstigator = GetInstigatorController();
	UGameplayStatics::ApplyDamage(OtherActor, Damage, PawnInstigator, this, UDamageType::StaticClass());

	Destroy();
}

void AShootProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalOffset(FVector(ProjectileSpeed * DeltaTime, 0.f, 0.f));
}
