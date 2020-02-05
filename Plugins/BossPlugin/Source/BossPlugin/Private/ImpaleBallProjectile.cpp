#include "ImpaleBallProjectile.h"
#include "BossPlugin.h"
#include "GameFramework/DamageType.h"
#include "DamageableComponent.h"

AImpaleBallProjectile::AImpaleBallProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	SphereComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	SphereComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &AImpaleBallProjectile::OnOverlap);
}

void AImpaleBallProjectile::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	check(Other);

	UDamageableComponent* DamageableComponent = Other->FindComponentByClass<UDamageableComponent>();

	if (IsValid(DamageableComponent) == false)
	{
		UE_LOG(LogBossPlugin, Error, TEXT("AImpaleBallProjectile::OnOverlap IsValid(Character) == false"));
		return;
	}

	DamageableComponent->TakeDamage(ImpactDamage);
}

void AImpaleBallProjectile::BeginPlay()
{
}

void AImpaleBallProjectile::Tick(float DeltaTime)
{
	// Super::Tick(DeltaTime);

	FVector Location = GetActorLocation();
	FVector NewLocation = Location + GetActorForwardVector().GetSafeNormal() * DeltaTime * 1000;
	SetActorLocation(NewLocation);
}

