// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BossAIController.generated.h"

/**
 * 
 */
UCLASS()
class BOSSPLUGIN_API ABossAIController : public AAIController
{
	GENERATED_BODY()

public:
	void UseRandomAbility();

protected:
	ABossAIController();
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly)
	UBehaviorTree* BehaviorTree;

	UPROPERTY()
	UBehaviorTreeComponent* BehaviorTreeComponent;

	UPROPERTY()
	UBlackboardComponent* BlackboardComponent;
};
