#include "BossAIController.h"
#include "BossPlugin.h"
#include "GameFramework/Pawn.h"
#include "BossCharacter.h"
#include "BossAbility.h"

void ABossAIController::UseRandomAbility()
{
	APawn* Pawn = GetPawn();

	if (IsValid(Pawn) == false)
	{
		UE_LOG(LogBossPlugin, Error, TEXT("ABossAIController::UseRandomAbility IsValid(Pawn) == false"));
		return;
	}

	ABossCharacter* BossCharacter = Cast<ABossCharacter>(Pawn);

	if (IsValid(BossCharacter) == false)
	{
		UE_LOG(LogBossPlugin, Error, TEXT("ABossAIController::UseRandomAbility IsValid(BossCharacter) == false"));
		return;
	}

	UBossAbility* RandomAbility = BossCharacter->GetRandomAbility();

	if (IsValid(RandomAbility) == false)
	{
		UE_LOG(LogBossPlugin, Error, TEXT("ABossAIController::UseRandomAbility IsValid(RandomAbility) == false"));
		return;
	}

	RandomAbility->Activate(BossCharacter->GetPhase());
}
