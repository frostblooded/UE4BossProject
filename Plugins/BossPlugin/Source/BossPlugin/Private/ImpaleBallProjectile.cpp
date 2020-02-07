#include "ImpaleBallProjectile.h"
#include "BossPlugin.h"
#include "GameFramework/DamageType.h"
#include "Spike.h"
#include "GameFramework/Actor.h"
#include "Math/Rotator.h"
#include "MobCharacter.h"
#include "DamageableComponent.h"

AImpaleBallProjectile::AImpaleBallProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	SphereComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	SphereComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &AImpaleBallProjectile::OnOverlap);
	RootComponent = SphereComponent;
}

void AImpaleBallProjectile::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	check(Other);

	AMobCharacter* OtherMobCharacter = Cast<AMobCharacter>(Other);

	// Don't deal damage if you cast the ability or the ability hit a mob
	if (Other == GetInstigator() || OtherMobCharacter != nullptr)
	{
		return;
	}

	UDamageableComponent* DamageableComponent = Other->FindComponentByClass<UDamageableComponent>();

	if (IsValid(DamageableComponent) == false)
	{
		UE_LOG(LogBossPlugin, Error, TEXT("AImpaleBallProjectile::OnOverlap IsValid(Character) == false"));
		return;
	}

	DamageableComponent->TakeDamage(ImpactDamage);
	Destroy();
}

void AImpaleBallProjectile::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();

	if (IsValid(World) == false)
	{
		UE_LOG(LogBossPlugin, Error, TEXT("AImpaleBallProjectile::BeginPlay IsValid(World) == false"))
		return;
	}

	TimerManager = &World->GetTimerManager();
	TimerManager->SetTimer(SpikeBurstTimerHandle, this, &AImpaleBallProjectile::OnSpikeBurstTimerExpired, DelayBetweenSpikeBursts, true);
}

void AImpaleBallProjectile::BeginDestroy()
{
	if (TimerManager)
	{
		TimerManager->ClearTimer(SpikeBurstTimerHandle);
		TimerManager = nullptr;
	}

	Super::BeginDestroy();
}

void AImpaleBallProjectile::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FVector Location = GetActorLocation();
	FVector NewLocation = Location + GetActorForwardVector().GetSafeNormal() * DeltaSeconds * Speed;
	SetActorLocation(NewLocation);
}

void AImpaleBallProjectile::OnSpikeBurstTimerExpired()
{
	SpawnSpikeBurst();
	SpikeBurstsDone++;

	if (SpikeBurstsDone >= GetSpikeBurstsCap())
	{
		Destroy();
	}
}

void AImpaleBallProjectile::SpawnSpikeBurst()
{
	int SpikesToSpawn = GetSpikesCountInBurst();
	UWorld* World = GetWorld();

	if (IsValid(World) == false)
	{
		UE_LOG(LogBossPlugin, Error, TEXT("ASpike::SpawnNextSpike() - IsValid(World) == false"));
		return;
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = GetOwner();
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = GetInstigator();

	float DegreesRotationForSpike = 360 / SpikesToSpawn;
	FVector RotationRadius(50, 0, 0);

	for (int i = 0; i < SpikesToSpawn; i++)
	{
		float RotationAngle = DegreesRotationForSpike * i;
		FVector RotatedVector = RotationRadius.RotateAngleAxis(RotationAngle, FVector::UpVector);
		FVector RotatedNewLocation = GetActorLocation() + RotatedVector;
		ASpike* NewSpike = World->SpawnActor<ASpike>(SpikeTemplate, RotatedNewLocation, FRotator(0, RotationAngle, 0), SpawnParams);
		
		if (IsValid(NewSpike) == false)
		{
			UE_LOG(LogBossPlugin, Error, TEXT("ASpike::SpawnNextSpike() - IsValid(NewSpike) == false"));
			return;
		}
	}
}

int AImpaleBallProjectile::GetSpikesCountInBurst()
{
	if (PhaseModifier == 1)
	{
		return 4;
	}
	else if (PhaseModifier == 2)
	{
		return 6;
	}

	return 8;
}

int AImpaleBallProjectile::GetSpikeBurstsCap()
{
	if (PhaseModifier == 1)
	{
		return 1;
	}
	else if (PhaseModifier == 2)
	{
		return 2;
	}

	return 3;
}

