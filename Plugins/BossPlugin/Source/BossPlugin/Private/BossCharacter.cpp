// Fill out your copyright notice in the Description page of Project Settings.


#include "BossCharacter.h"
#include "BossPlugin.h"

ABossCharacter::ABossCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABossCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	Health = MaxHealth;
}

int ABossCharacter::GetPhase()
{
	if (Health > PhaseTwoThreshold)
	{
		return 1;
	}
	else if (Health > PhaseThreeThreshold && Health <= PhaseTwoThreshold)
	{
		return 2;
	}

	return 3;
}

TArray<UBossAbility*> ABossCharacter::GetPhaseAbilities()
{
	int Phase = GetPhase();

	if (Phase == 1)
	{
		return PhaseOneAbilitiesInstances;
	}
	else if (Phase == 2)
	{
		return PhaseTwoAbilitiesInstances;
	}

	return PhaseThreeAbilitiesInstances;
}

UBossAbility* ABossCharacter::GetRandomAbility()
{
	TArray<UBossAbility*> Abilities = GetPhaseAbilities();

	if (Abilities.Num() == 0)
	{
		UE_LOG(LogBossPlugin, Error, TEXT("ABossAIController::UseRandomAbility Abilities.Num == 0"));
		return nullptr;
	}

	int RandomAbilityIndex = FMath::RandRange(1, Abilities.Num());
	return Abilities[RandomAbilityIndex];
}
