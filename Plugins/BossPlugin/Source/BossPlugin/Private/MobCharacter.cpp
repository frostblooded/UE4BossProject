#include "MobCharacter.h"

AMobCharacter::AMobCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	DamageableComponent = CreateDefaultSubobject<UDamageableComponent>(TEXT("Damageable"));

	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ExplosionParticleSystem"));
	ParticleSystemComponent->bAutoActivate = false;
}
