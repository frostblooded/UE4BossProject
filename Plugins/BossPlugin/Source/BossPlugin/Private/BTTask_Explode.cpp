#include "BTTask_Explode.h"
#include "MobAIController.h"
#include "BossPlugin.h"

EBTNodeResult::Type UBTTask_Explode::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AMobAIController* MobAIController = Cast<AMobAIController>(OwnerComp.GetOwner());

	if (IsValid(MobAIController) == false)
	{
		UE_LOG(LogBossPlugin, Error, TEXT("UBTTask_Explode::ExecuteTask IsValid(MobAIController) == false"));
		return EBTNodeResult::Failed;
	}
	
	if (MobAIController->Explode())
	{
		return EBTNodeResult::Succeeded;
	}
	else
	{
		return EBTNodeResult::Failed;
	}
}
