// Fill out your copyright notice in the Description page of Project Settings.


#include "BossAbility.h"
#include "BossPlugin.h"
#include "Engine/World.h"

bool UBossAbility::Activate()
{
	if (bIsOffCooldown == false)
	{
		return false;
	}

    UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogBossPlugin, Error, TEXT("UBossAbility::Activate IsValid(World) == false"));
		return false;
	}
	
    TimerManager = &World->GetTimerManager();
    TimerManager->SetTimer(CooldownTimerHandle, this, &UBossAbility::OnCooldownTimerExpired, CooldownTime);
    bIsOffCooldown = false;

	AActor* Owner = Cast<AActor>(GetOuter());
	if (IsValid(Owner) == false)
	{
		UE_LOG(LogBossPlugin, Error, TEXT("UBossAbility::Activate IsValid(Owner) == false"));
		return false;
	}

    OnActivateBlueprint(Owner);
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
