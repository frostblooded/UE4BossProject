// Fill out your copyright notice in the Description page of Project Settings.


#include "ImpaleBallAbility.h"
#include "Engine/World.h"
#include "BossPluginUtils.h"
#include "BossPlugin.h"

bool UImpaleBallAbility::Activate(int PhaseModifier)
{
	UWorld* World = GetWorld();

	if (IsValid(World) == false)
	{
		UE_LOG(LogBossPlugin, Error, TEXT("UImpaleBallAbility::Activate() IsValid(World) == false"));
		return false;
	}

	APawn* Owner = Cast<APawn>(GetOuter());

	if (IsValid(Owner) == false)
	{
		UE_LOG(LogBossPlugin, Error, TEXT("UImpaleBallAbility::Activate() IsValid(Owner) == false"));
		return false;
	}

	FActorSpawnParameters ActorSpawnParameters;
	ActorSpawnParameters.Owner = Owner;
	ActorSpawnParameters.Instigator = Owner;
	ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector PlayerLocation = FBossPluginUtils::GetPlayerLocation(GetWorld());
	FVector Direction = PlayerLocation - Owner->GetActorLocation();
	Direction.Z = 0.0f;
	Direction.Normalize();

	FVector SpawnLocation = Owner->GetActorLocation();

	AActor* Projectile = World->SpawnActor<AActor>(ImpaleBallClass, SpawnLocation, Direction.Rotation(), ActorSpawnParameters);

	if (IsValid(Projectile) == false)
	{
		UE_LOG(LogBossPlugin, Error, TEXT("UImpaleBallAbility::Activate IsValid(Projectile) == false"));
		return false;
	}

	AImpaleBallProjectile* ImpaleBallProjectile = Cast<AImpaleBallProjectile>(Projectile);

	if (IsValid(ImpaleBallProjectile) == false)
	{
		UE_LOG(LogBossPlugin, Error, TEXT("UImpaleBallAbility::Activate IsValid(ImpaleBallProjectile) == false"));
		return false;
	}

	ImpaleBallProjectile->PhaseModifier = PhaseModifier;

	return true;
}
