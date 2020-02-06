#include "MobCharacter.h"

AMobCharacter::AMobCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	DamageableComponent = CreateDefaultSubobject<UDamageableComponent>(TEXT("Damageable"));
}

void AMobCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMobCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
