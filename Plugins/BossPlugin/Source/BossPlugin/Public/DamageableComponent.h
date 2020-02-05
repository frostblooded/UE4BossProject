// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DamageableComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOSSPLUGIN_API UDamageableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDamageableComponent();

	UFUNCTION()
	void TakeDamage(float Damage);

	UFUNCTION()
	void Die();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MaxHealth = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Health;

protected:
	virtual void BeginPlay() override;
};
