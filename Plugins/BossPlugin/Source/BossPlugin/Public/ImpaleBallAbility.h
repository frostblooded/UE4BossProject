// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BossAbility.h"
#include "ImpaleBallProjectile.h"
#include "ImpaleBallAbility.generated.h"

/**
 * 
 */
UCLASS()
class BOSSPLUGIN_API UImpaleBallAbility : public UBossAbility
{
	GENERATED_BODY()
	
public:
	virtual bool Activate() override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AImpaleBallProjectile> ImpaleBallClass;
};
