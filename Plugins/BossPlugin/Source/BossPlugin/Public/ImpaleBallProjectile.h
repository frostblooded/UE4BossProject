// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "TimerManager.h"
#include "Spike.h"
#include "ImpaleBallProjectile.generated.h"

UCLASS()
class BOSSPLUGIN_API AImpaleBallProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(VisibleAnywhere, Category = Gameplay)
	USphereComponent* SphereComponent;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ASpike> SpikeTemplate;

	UPROPERTY(EditAnywhere)
	float ImpactDamage = 10;

	UPROPERTY(EditAnywhere)
	float Speed = 500;
	
	UPROPERTY(EditDefaultsOnly)
	int PhaseModifier = 1;

	UPROPERTY(EditDefaultsOnly)
	float DelayBetweenSpikeBursts = 1;

	AImpaleBallProjectile();

protected:
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	int SpikeBurstsDone = 0;

    FTimerManager* TimerManager = nullptr;
    FTimerHandle SpikeBurstTimerHandle;

    void OnSpikeBurstTimerExpired();
	int GetSpikeBurstsCap();
	void SpawnSpikeBurst();
	int GetSpikesCountInBurst();

public:	
	virtual void Tick(float DeltaSeconds) override;
};
