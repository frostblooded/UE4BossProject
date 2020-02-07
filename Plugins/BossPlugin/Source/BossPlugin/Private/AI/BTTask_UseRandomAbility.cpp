// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/BTTask_UseRandomAbility.h"
#include "BossPlugin.h"
#include "BossAIController.h"

EBTNodeResult::Type UBTTask_UseRandomAbility::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	ABossAIController* BossAIController = Cast<ABossAIController>(OwnerComp.GetOwner());

	if (IsValid(BossAIController) == false)
	{
		UE_LOG(LogBossPlugin, Error, TEXT("UBTTask_UseRandomAbility::ExecuteTask IsValid(BossAIController) == false"));
		return EBTNodeResult::Failed;
	}
	
	if (BossAIController->UseRandomAbility())
	{
		return EBTNodeResult::Succeeded;
	}
	else
	{
		return EBTNodeResult::Failed;
	}
}
