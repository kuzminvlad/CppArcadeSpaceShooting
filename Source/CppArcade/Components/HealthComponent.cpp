// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthComponent.h"

UHealthComponent::UHealthComponent()
{
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnOwnerDamaged);
}

void UHealthComponent::OnOwnerDamaged(AActor* DamagedActor, float Damage, const UDamageType* Damagetype, AController* DamageInstigator, AActor* DamageCauser)
{
	ChangeHealth(-Damage);
}

void UHealthComponent::ChangeHealth(float Value)
{
	Health += Value;
	Health = (Health > HealthMax) ? HealthMax : Health;
	if (Health <= 0.f)
	{
		GetOwner()->OnTakeAnyDamage.RemoveDynamic(this, &UHealthComponent::OnOwnerDamaged);
		OnHealthEnded.Broadcast();
	}
}

float UHealthComponent::GetHealth()
{
	return Health;
}

float UHealthComponent::GetHealthMax()
{
	return HealthMax;
}
