// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ImpaleMovementComponent.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "BossPlugin.h"
#include "Spike.generated.h"

UCLASS()
class BOSSPLUGIN_API ASpike : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpike();
protected:
	UPROPERTY(VisibleAnywhere, Category = Gameplay)
	UBoxComponent* BoxComponent;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, Category = Gameplay)
	int32 RemainingSpikes = 6;

	UPROPERTY(EditAnywhere)
	float Damage = 10;

	UPROPERTY(VisibleAnywhere)
	UImpaleMovementComponent* ImpaleMovementComponent;

	virtual void BeginPlay() override;

	UFUNCTION()
	void TrySpawnNextSpike();

	UFUNCTION()
	void SpawnNextSpike();

	UFUNCTION()
	void DestroySelf();

	UFUNCTION()
	static void DisablePlayerInput(APawn* Pawn);

	UFUNCTION()
	static void EnablePlayerInput(APawn* Pawn);

private:
	FVector GetSpawnLocation();
	float GetBoxHeight();
	void DamageActor(AActor* Actor);
};
