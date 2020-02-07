// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTreeAIController.generated.h"

UCLASS()
class BOSSPLUGIN_API ABehaviorTreeAIController : public AAIController
{
	GENERATED_BODY()

public:
	ABehaviorTreeAIController();

	UPROPERTY(EditDefaultsOnly)
	UBehaviorTree* BehaviorTree;

	UPROPERTY()
	UBehaviorTreeComponent* BehaviorTreeComponent;

	UPROPERTY()
	UBlackboardComponent* BlackboardComponent;
	
protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;
};
