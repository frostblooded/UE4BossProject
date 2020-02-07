// Fill out your copyright notice in the Description page of Project Settings.


#include "BossPlugin.h"
#include "MobCharacter.h"
#include "MobAIController.h"
#include "SpawnMobsAbility.h"

bool USpawnMobsAbility::Activate(int PhaseModifier)
{
	int SpawnCount = GetSpawnedMobsCount(PhaseModifier);
	UWorld* World = GetWorld();

	if (IsValid(World) == false)
	{
		UE_LOG(LogBossPlugin, Error, TEXT("USpawnMobsAbility::Activate IsValid(World) == false"));
		return false;
	}

	UObject* Outer = GetOuter();

	if (IsValid(Outer) == false)
	{
		UE_LOG(LogBossPlugin, Error, TEXT("USpawnMobsAbility::Activate IsValid(Outer) == false"));
		return false;
	}

	APawn* Pawn = Cast<APawn>(Outer);

	if (IsValid(Pawn) == false)
	{
		UE_LOG(LogBossPlugin, Error, TEXT("USpawnMobsAbility::Activate IsValid(Pawn) == false"));
		return false;
	}

	for (int i = 0; i < SpawnCount; i++)
	{
		FActorSpawnParameters ActorSpawnParameters;
		ActorSpawnParameters.Owner = Pawn;
		ActorSpawnParameters.Instigator = Pawn;
		ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		AMobCharacter* NewMobCharacter = World->SpawnActor<AMobCharacter>(MobCharacterTemplate, Pawn->GetActorLocation(), FRotator(), ActorSpawnParameters);

		if (IsValid(NewMobCharacter) == false)
		{
			UE_LOG(LogBossPlugin, Error, TEXT("USpawnMobsAbility::Activate IsValid(NewMobCharacter) == false"));
			return false;
		}

		APawn* NewPawn = Cast<APawn>(NewMobCharacter);

		if (IsValid(NewPawn) == false)
		{
			UE_LOG(LogBossPlugin, Error, TEXT("USpawnMobsAbility::Activate IsValid(NewPawn) == false"));
			return false;
		}

		NewPawn->SpawnDefaultController();
	}

	return true;
}

int USpawnMobsAbility::GetSpawnedMobsCount(int PhaseModifier)
{
	if (PhaseModifier == 1)
	{
		return 1;
	}
	else if (PhaseModifier == 2)
	{
		return 2;
	}

	return 3;
}
