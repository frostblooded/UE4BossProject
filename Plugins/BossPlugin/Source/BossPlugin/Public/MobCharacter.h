// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/Character.h"
#include "DamageableComponent.h"
#include "MobCharacter.generated.h"

UCLASS()
class BOSSPLUGIN_API AMobCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMobCharacter();

	UPROPERTY(VisibleAnywhere)
	UDamageableComponent* DamageableComponent;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* ParticleSystemComponent;

	UPROPERTY(EditAnywhere)
	float ExplosionDamage = 15;

	UPROPERTY(EditAnywhere)
	float ExplosionRadius = 20;
};
