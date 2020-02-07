// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BossAbility.h"
#include "TeleportAbility.generated.h"

/**
 * 
 */
UCLASS()
class BOSSPLUGIN_API UTeleportAbility : public UBossAbility
{
	GENERATED_BODY()
	
public:
	virtual bool Activate(int PhaseModifier) override;
};
