// Fill out your copyright notice in the Description page of Project Settings.


#include "BossAIController.h"
#include "BossPlugin.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"
#include "BossCharacter.h"
#include "BossAbility.h"
#include "Math/UnrealMathUtility.h"
#include "BossPluginUtils.h"
#include "BehaviorTree/BlackboardComponent.h"

ABossAIController::ABossAIController()
{
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviourTreeComponent"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
}

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

	RandomAbility->Activate(FVector());
}

void ABossAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (!IsValid(BehaviorTree))
	{
		UE_LOG(LogBossPlugin, Error, TEXT("ABossAIController::OnPosses IsValid(BehaviorTree) == false"));
		return;
	}

	if (!IsValid(BehaviorTree->BlackboardAsset))
	{
		UE_LOG(LogBossPlugin, Error, TEXT("ABossAIController::OnPosses IsValid(BehaviorTree->BlackboardAsset) == false"));
		return;
	}

	BlackboardComponent->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	BehaviorTreeComponent->StartTree(*BehaviorTree);
}

void ABossAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APawn* Player = FBossPluginUtils::GetPlayer(GetWorld());
	BlackboardComponent->SetValueAsObject(FName(TEXT("Player")), Player);
}
