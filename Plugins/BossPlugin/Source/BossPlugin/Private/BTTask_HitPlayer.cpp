#include "BTTask_HitPlayer.h"
#include "BossPlugin.h"
#include "BossPluginUtils.h"
#include "DamageableComponent.h"
#include "BossAIController.h"
#include "BossCharacter.h"

EBTNodeResult::Type UBTTask_HitPlayer::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	ABossAIController* BossAIController = Cast<ABossAIController>(OwnerComp.GetOwner());

	if (IsValid(BossAIController) == false)
	{
		UE_LOG(LogBossPlugin, Error, TEXT("UBTTask_HitPlayer::ExecuteTask IsValid(BossAIController) == false"));
		return EBTNodeResult::Failed;
	}

	ABossCharacter* BossCharacter = Cast<ABossCharacter>(BossAIController->GetPawn());

	if (IsValid(BossCharacter) == false)
	{
		UE_LOG(LogBossPlugin, Error, TEXT("UBTTask_HitPlayer::ExecuteTask IsValid(BossCharacter) == false"));
		return EBTNodeResult::Failed;
	}
	
	APawn* PlayerPawn = FBossPluginUtils::GetPlayer(GetWorld());

	if (IsValid(PlayerPawn) == false)
	{
		UE_LOG(LogBossPlugin, Error, TEXT("UBTTask_HitPlayer::ExecuteTask IsValid(PlayerPawn) == false"));
		return EBTNodeResult::Failed;
	}

	UDamageableComponent* PlayerDamageableComponent = PlayerPawn->FindComponentByClass<UDamageableComponent>();

	if (IsValid(PlayerDamageableComponent) == false)
	{
		UE_LOG(LogBossPlugin, Error, TEXT("UBTTask_HitPlayer::ExecuteTask IsValid(PlayerDamageableComponent) == false"));
		return EBTNodeResult::Failed;
	}

	PlayerDamageableComponent->TakeDamage(BossCharacter->MeleeDamage);
	return EBTNodeResult::Succeeded;
}
