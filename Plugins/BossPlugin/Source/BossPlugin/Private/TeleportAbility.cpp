#include "TeleportAbility.h"
#include "BossPlugin.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "BossPluginUtils.h"

bool UTeleportAbility::Activate(int PhaseModifier)
{
	APawn* PlayerPawn = FBossPluginUtils::GetPlayer(GetWorld());

	if (IsValid(PlayerPawn) == false)
	{
		UE_LOG(LogBossPlugin, Error, TEXT("UTeleportAbility::Activate IsValid(PlayerPawn) == false"));
		return false;
	}

	APawn* Owner = Cast<APawn>(GetOuter());

	if (IsValid(Owner) == false)
	{
		UE_LOG(LogBossPlugin, Error, TEXT("UTeleportAbility::Activate IsValid(Owner) == false"));
		return false;
	}

	UWorld* World = GetWorld();

	if (IsValid(World) == false)
	{
		UE_LOG(LogBossPlugin, Error, TEXT("UTeleportAbility::Activate IsValid(World) == false"));
		return false;
	}

	FHitResult OutHit;
	FVector ActorLocation = PlayerPawn->GetActorLocation();
	FVector ActorForwardVector = PlayerPawn->GetActorForwardVector();
	FVector LineTraceStart = ActorLocation + ActorForwardVector * 100;
	FVector LineTraceEnd = ActorLocation + PlayerPawn->GetActorForwardVector() * 500;
	bool bIsHit = World->LineTraceSingleByChannel(OutHit, LineTraceStart, LineTraceEnd, ECollisionChannel::ECC_WorldStatic);

	if (bIsHit)
	{
		return Owner->SetActorLocation(OutHit.ImpactPoint);
	}

	return Owner->SetActorLocation(LineTraceEnd);
}
