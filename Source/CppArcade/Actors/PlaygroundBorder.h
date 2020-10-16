// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "PlaygroundBorder.generated.h"

UCLASS()
class CPPARCADE_API APlaygroundBorder : public AActor
{
	GENERATED_BODY()
	
public:
	APlaygroundBorder();

	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBoxComponent* Trigger;
};
