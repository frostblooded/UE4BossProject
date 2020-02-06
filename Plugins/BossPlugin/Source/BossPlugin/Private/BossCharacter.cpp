// Fill out your copyright notice in the Description page of Project Settings.


#include "BossCharacter.h"
#include "BossPlugin.h"

ABossCharacter::ABossCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	DamageableComponent = CreateDefaultSubobject<UDamageableComponent>(TEXT("Damageable"));
}

void ABossCharacter::BeginPlay()
{
	Super::BeginPlay();

	InstantiateAbilities();
}

void ABossCharacter::InstantiateAbilities()
{
	for (auto Template : PhaseOneAbilitiesTemplates)
	{
		PhaseOneAbilitiesInstances.Add(NewObject<UBossAbility>(this, Template));
	}

	for (auto Template : PhaseTwoAbilitiesTemplates)
	{
		PhaseTwoAbilitiesInstances.Add(NewObject<UBossAbility>(this, Template));
	}

	for (auto Template : PhaseThreeAbilitiesTemplates)
	{
		PhaseThreeAbilitiesInstances.Add(NewObject<UBossAbility>(this, Template));
	}
}

int ABossCharacter::GetPhase()
{
	if (DamageableComponent->Health > PhaseTwoThreshold)
	{
		return 1;
	}
	else if (DamageableComponent->Health > PhaseThreeThreshold && DamageableComponent->Health <= PhaseTwoThreshold)
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

	int RandomAbilityIndex = FMath::RandRange(0, Abilities.Num() - 1);
	return Abilities[RandomAbilityIndex];
}
