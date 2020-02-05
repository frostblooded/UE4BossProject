// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BossAbility.h"
#include "DamageableComponent.h"
#include "BossCharacter.generated.h"

UCLASS()
class BOSSPLUGIN_API ABossCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABossCharacter();

	UPROPERTY(VisibleAnywhere)
	UDamageableComponent* DamageableComponent;

	UPROPERTY(EditDefaultsOnly)
	TArray<UBossAbility*> PhaseOneAbilitiesTemplates;

	UPROPERTY(EditDefaultsOnly)
	TArray<UBossAbility*> PhaseTwoAbilitiesTemplates;

	UPROPERTY(EditDefaultsOnly)
	TArray<UBossAbility*> PhaseThreeAbilitiesTemplates;

	UPROPERTY(EditAnywhere)
	float PhaseTwoThreshold = 70;

	UPROPERTY(EditAnywhere)
	float PhaseThreeThreshold = 30;

	UFUNCTION()
	int GetPhase();

	UFUNCTION()
	TArray<UBossAbility*> GetPhaseAbilities();

	UFUNCTION()
	UBossAbility* GetRandomAbility();

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	TArray<UBossAbility*> PhaseOneAbilitiesInstances;

	UPROPERTY()
	TArray<UBossAbility*> PhaseTwoAbilitiesInstances;

	UPROPERTY()
	TArray<UBossAbility*> PhaseThreeAbilitiesInstances;
};
