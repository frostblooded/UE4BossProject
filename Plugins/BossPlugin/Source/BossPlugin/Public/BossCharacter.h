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

	UPROPERTY(EditAnywhere)
	float MeleeDamage = 10;

	UPROPERTY(VisibleAnywhere)
	UDamageableComponent* DamageableComponent;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UBossAbility>> PhaseOneAbilitiesTemplates;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UBossAbility>> PhaseTwoAbilitiesTemplates;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UBossAbility>> PhaseThreeAbilitiesTemplates;

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

	UFUNCTION()
	bool HasAbilityOffCooldown();

protected:
	virtual void BeginPlay() override;
	void InstantiateAbilities();

	UPROPERTY()
	TArray<UBossAbility*> PhaseOneAbilitiesInstances;

	UPROPERTY()
	TArray<UBossAbility*> PhaseTwoAbilitiesInstances;

	UPROPERTY()
	TArray<UBossAbility*> PhaseThreeAbilitiesInstances;
};
