// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTreeAIController.h"
#include "MobAIController.generated.h"

/**
 * 
 */
UCLASS()
class BOSSPLUGIN_API AMobAIController : public ABehaviorTreeAIController
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	bool Explode();

	UFUNCTION()
	void DealExplosionDamage();

	UFUNCTION()
	void DealExplosionDamageTo(AActor* Actor);
};
