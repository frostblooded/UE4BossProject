// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageableComponent.h"
#include "GameFramework/Actor.h"
#include "BossPlugin.h"

UDamageableComponent::UDamageableComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UDamageableComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
}

void UDamageableComponent::TakeDamage(float Damage)
{
	Health -= Damage;
	// UE_LOG(LogBossPlugin, Display, TEXT("%s takes %f damage and is left at %f health"), GetName(), Damage, Health);

	if (Health <= 0)
	{
		Die();
	}
}

void UDamageableComponent::Die()
{
	AActor* Owner = GetOwner();

	if (IsValid(Owner) == false)
	{
		UE_LOG(LogBossPlugin, Error, TEXT("UDamageableComponent::DealDamage IsValid(Owner) == false"));
	}

	Owner->Destroy();
}
