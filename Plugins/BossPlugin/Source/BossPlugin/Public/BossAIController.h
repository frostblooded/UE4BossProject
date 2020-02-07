// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTreeAIController.h"
#include "BossAIController.generated.h"

/**
 * 
 */
UCLASS()
class BOSSPLUGIN_API ABossAIController : public ABehaviorTreeAIController
{
	GENERATED_BODY()

public:
	bool UseRandomAbility();

protected:
	virtual void Tick(float DeltaTime) override;
};
