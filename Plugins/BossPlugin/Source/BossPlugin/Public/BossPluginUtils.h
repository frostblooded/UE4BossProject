// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

/**
 * 
 */
static class BOSSPLUGIN_API FBossPluginUtils
{
public:
	static APawn* GetPlayer(UWorld* World);
	static FVector GetPlayerLocation(UWorld* World);
};
