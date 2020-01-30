// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "BossPlugin.h"

DEFINE_LOG_CATEGORY(LogBossPlugin)

#define LOCTEXT_NAMESPACE "FBossPluginModule"

void FBossPluginModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FBossPluginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FBossPluginModule, BossPlugin)