// Fill out your copyright notice in the Description page of Project Settings.


#include "BossPluginUtils.h"
#include "BossPlugin.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

APawn* FBossPluginUtils::GetPlayer(UWorld* World)
{
	if (IsValid(World) == false)
	{
		UE_LOG(LogBossPlugin, Error, TEXT("ABossAIController::GetPlayer IsValid(World) == false"));
		return nullptr;
	}

	APlayerController* PlayerController = World->GetFirstPlayerController();

	if (!IsValid(PlayerController))
	{
		UE_LOG(LogBossPlugin, Error, TEXT("ABossAIController::GetPlayer IsValid(PlayerController) == false"));
		return nullptr;
	}

	return PlayerController->GetPawn();
}

FVector FBossPluginUtils::GetPlayerLocation(UWorld* World)
{
	APawn* PlayerPawn = GetPlayer(World);

	if (!IsValid(PlayerPawn))
	{
		UE_LOG(LogBossPlugin, Error, TEXT("ABossAIController::GetPlayerLocation IsValid(PlayerController) == false"));
		return FVector();
	}

	return PlayerPawn->GetActorLocation();
}
