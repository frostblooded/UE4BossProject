// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BossAbility.h"
#include "MobCharacter.h"
#include "SpawnMobsAbility.generated.h"

/**
 * 
 */
UCLASS()
class BOSSPLUGIN_API USpawnMobsAbility : public UBossAbility
{
	GENERATED_BODY()
	
public:
	virtual bool Activate(int PhaseModifier) override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AMobCharacter> MobCharacterTemplate;

protected:
	int GetSpawnedMobsCount(int PhaseModifier);
};
