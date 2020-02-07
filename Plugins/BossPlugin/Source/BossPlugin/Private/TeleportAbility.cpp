#include "TeleportAbility.h"
#include "BossPlugin.h"
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

	FVector TeleportLocation = PlayerPawn->GetActorLocation() + PlayerPawn->GetActorForwardVector() * 500;
	return Owner->SetActorLocation(TeleportLocation);
}
