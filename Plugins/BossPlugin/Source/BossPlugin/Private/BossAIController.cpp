#include "BossAIController.h"
#include "BossPlugin.h"
#include "GameFramework/Pawn.h"
#include "BossCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BossAbility.h"

bool ABossAIController::UseRandomAbility()
{
	APawn* Pawn = GetPawn();

	if (IsValid(Pawn) == false)
	{
		UE_LOG(LogBossPlugin, Error, TEXT("ABossAIController::UseRandomAbility IsValid(Pawn) == false"));
		return false;
	}

	ABossCharacter* BossCharacter = Cast<ABossCharacter>(Pawn);

	if (IsValid(BossCharacter) == false)
	{
		UE_LOG(LogBossPlugin, Error, TEXT("ABossAIController::UseRandomAbility IsValid(BossCharacter) == false"));
		return false;
	}

	UBossAbility* RandomAbility = BossCharacter->GetRandomAbility();

	if (IsValid(RandomAbility) == false)
	{
		UE_LOG(LogBossPlugin, Error, TEXT("ABossAIController::UseRandomAbility IsValid(RandomAbility) == false"));
		return false;
	}

	return RandomAbility->TryActivate(BossCharacter->GetPhase());
}

void ABossAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsValid(BlackboardComponent))
	{
		APawn* Pawn = GetPawn();

		if (IsValid(Pawn) == false)
		{
			UE_LOG(LogBossPlugin, Error, TEXT("ABossAIController::Tick IsValid(Pawn) == false"));
		}

		ABossCharacter* BossCharacter = Cast<ABossCharacter>(Pawn);

		if (IsValid(BossCharacter) == false)
		{
			UE_LOG(LogBossPlugin, Error, TEXT("ABossAIController::Tick IsValid(BossCharacter) == false"));
		}

		BlackboardComponent->SetValueAsBool(TEXT("HasAbilityOffCooldown"), BossCharacter->HasAbilityOffCooldown());
	}
}

