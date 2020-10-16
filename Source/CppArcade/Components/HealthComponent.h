// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHealthEndedEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPPARCADE_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	float Health = 100.f;
	float HealthMax = 100.f;

	UFUNCTION()
	void OnOwnerDamaged(AActor* DamagedActor, float Damage, const UDamageType* Damagetype, AController* DamageInstigator, AActor* DamageCauser);

public:
	UHealthComponent();

	UFUNCTION(BlueprintCallable, Category = "Health")
	void ChangeHealth(float Value);

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealth();

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthMax();

	UPROPERTY(BlueprintAssignable, Category = "Health")
	FHealthEndedEvent OnHealthEnded;
};
