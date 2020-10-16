// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "./EntityPawn.h"
#include "PlayerPawn.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPawnDamagedEvent);

UCLASS()
class CPPARCADE_API APlayerPawn : public AEntityPawn
{
	GENERATED_BODY()

public:
	APlayerPawn();

protected:
	virtual void BeginPlay() override;
	void OnTouchMove(ETouchIndex::Type FingerIndex, FVector Location);
	void OnTouchPress(ETouchIndex::Type FingerIndex, FVector Location);
	virtual void PossessedBy(AController* NewController) override;
	virtual float TakeDamage(float Damage, const FDamageEvent& DamageEvent, AController* InstigatedBy, AActor* DamageCauser) override;

	FVector2D TouchLocation;
	UMaterialInterface* PawnMaterial;
	class APlayerController* PlayerController;

	UPROPERTY(BlueprintReadOnly, Category = "Shooting")
	int CurrentShootLevel = 0;

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")
	class UCameraComponent* PawnCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Controlls")
	float TouchMoveSensivity = 1.f;

	UPROPERTY(BlueprintReadWrite, Category = "Health")
	bool bCanRecieveDamage = true;

	UPROPERTY(BlueprintAssignable, Category = "Health")
	FPawnDamagedEvent PawnDamaged;

	UFUNCTION(BlueprintPure, BlueprintNativeEvent, Category = "Health")
	bool CanBeDamaged();
	bool CanBeDamaged_Implementation();

	UFUNCTION(BlueprintCallable, Category = "Game")
	void ChangeShootLevel(int Value);

	UPROPERTY(editDefaultsOnly, BlueprintReadOnly, Category = "Pawn")
	UMaterialInterface* RecoverMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visual")
	UParticleSystem* DestroyParticle;
};
