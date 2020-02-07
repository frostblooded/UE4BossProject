#include "MobAIController.h"
#include "MobCharacter.h"
#include "DrawDebugHelpers.h"
#include "BossPlugin.h"

bool AMobAIController::Explode()
{
	AMobCharacter* MobCharacter = Cast<AMobCharacter>(GetPawn());

	if (IsValid(MobCharacter) == false)
	{
		UE_LOG(LogBossPlugin, Error, TEXT("AMobAIController::Explode IsValid(MobCharacter) == false"));
		return false;
	}

	if (IsValid(MobCharacter->ParticleSystemComponent))
	{
		MobCharacter->ParticleSystemComponent->Activate();
	}
	else
	{
		UE_LOG(LogBossPlugin, Error, TEXT("AMobAIController::Explode IsValid(MobCharacter->ParticleSystemComponent) == false"));
		return false;
	}

	DealExplosionDamage();

	if (GetPawn()->Destroy() == false)
	{
		UE_LOG(LogBossPlugin, Error, TEXT("AMobAIController::Explode GetPawn()->Destroy() == false"));
		return false;
	}

	return true;
}

void AMobAIController::DealExplosionDamage()
{
	APawn* Pawn = GetPawn();

	if (IsValid(Pawn) == false)
	{
		UE_LOG(LogBossPlugin, Error, TEXT("AMobAIController::DealExplosionDamage IsValid(Pawn) == false"));
		return;
	}

	AMobCharacter* MobCharacter = Cast<AMobCharacter>(Pawn);

	if (IsValid(MobCharacter) == false)
	{
		UE_LOG(LogBossPlugin, Error, TEXT("AMobAIController::DealExplosionDamage IsValid(MobCharacter) == false"));
		return;
	}

	UWorld* World = GetWorld();

	if (IsValid(World) == false)
	{
		UE_LOG(LogBossPlugin, Error, TEXT("AMobAIController::DealExplosionDamage IsValid(World) == false"));
		return;
	}

	TArray<FHitResult> OutHits;
	FCollisionShape CollisionSphere = FCollisionShape::MakeSphere(MobCharacter->ExplosionRadius);
	FVector ActorLocation = Pawn->GetActorLocation();
	bool bIsHit = World->SweepMultiByChannel(OutHits, ActorLocation, ActorLocation + 1, FQuat::Identity, ECC_Pawn, CollisionSphere);

	if (bIsHit)
	{
		for (FHitResult& Hit : OutHits)
		{
			AActor* OtherActor = Hit.Actor.Get();
			AMobCharacter* OtherMobCharacter = Cast<AMobCharacter>(OtherActor);

			if (OtherMobCharacter)
			{
				continue;
			}

			DealExplosionDamageTo(OtherActor);
		}
	}
}

void AMobAIController::DealExplosionDamageTo(AActor* Actor)
{
	UDamageableComponent* DamageableComponent = Actor->FindComponentByClass<UDamageableComponent>();

	if (IsValid(DamageableComponent) == false)
	{
		return;
	}

	APawn* Pawn = GetPawn();

	if (IsValid(Pawn) == false)
	{
		UE_LOG(LogBossPlugin, Error, TEXT("AMobAIController::DealExplosionDamageTo IsValid(Pawn) == false"));
		return;
	}

	AMobCharacter* MobCharacter = Cast<AMobCharacter>(Pawn);

	if (IsValid(MobCharacter) == false)
	{
		UE_LOG(LogBossPlugin, Error, TEXT("AMobAIController::DealExplosionDamageTo IsValid(MobCharacter) == false"));
		return;
	}

	DamageableComponent->TakeDamage(MobCharacter->ExplosionDamage);
}

