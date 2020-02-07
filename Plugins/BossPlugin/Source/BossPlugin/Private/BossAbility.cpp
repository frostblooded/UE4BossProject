// Fill out your copyright notice in the Description page of Project Settings.


#include "BossAbility.h"
#include "BossPlugin.h"
#include "Engine/World.h"

bool UBossAbility::TryActivate(int PhaseModifier)
{
	if (bIsOffCooldown == false)
	{
		return false;
	}

	Activate(PhaseModifier);

    UWorld* World = GetWorld();

	if (IsValid(World) == false)
	{
		UE_LOG(LogBossPlugin, Error, TEXT("UBossAbility::Activate IsValid(World) == false"));
		return false;
	}
	
    TimerManager = &World->GetTimerManager();
    TimerManager->SetTimer(CooldownTimerHandle, this, &UBossAbility::OnCooldownTimerExpired, CooldownTime);
    bIsOffCooldown = false;

	return true;
}

void UBossAbility::OnCooldownTimerExpired()
{
    bIsOffCooldown = true;
}

void UBossAbility::BeginDestroy()
{
	if (TimerManager)
	{
		TimerManager->ClearTimer(CooldownTimerHandle);
		TimerManager = nullptr;
	}
    Super::BeginDestroy();
}
