// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TimerManager.h"
#include "BossAbility.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class BOSSPLUGIN_API UBossAbility : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	float CooldownTime = 1.f;

	UFUNCTION(BlueprintCallable)
	virtual bool Activate(FVector AimLocation);

    UFUNCTION(BlueprintImplementableEvent)
	void OnActivateBlueprint(AActor* Source);

    UFUNCTION(BlueprintCallable)
	bool IsOffCooldown() const { return bIsOffCooldown; }

	virtual void BeginDestroy();

private:
	bool bIsOffCooldown = true;
	FTimerManager* TimerManager = nullptr;
	FTimerHandle CooldownTimerHandle;
	void OnCooldownTimerExpired();
};
