#include "BehaviorTreeAIController.h"
#include "BossPlugin.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BossPluginUtils.h"
#include "BehaviorTree/BlackboardComponent.h"

ABehaviorTreeAIController::ABehaviorTreeAIController()
{
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviourTreeComponent"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
}

void ABehaviorTreeAIController::OnPossess(APawn* InPawn)
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

void ABehaviorTreeAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APawn* Player = FBossPluginUtils::GetPlayer(GetWorld());
	BlackboardComponent->SetValueAsObject(FName(TEXT("Player")), Player);
}
