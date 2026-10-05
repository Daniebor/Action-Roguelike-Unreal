// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueExplosiveBarrel.h"

#include "NiagaraFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicsEngine/RadialForceComponent.h"


// Sets default values
ARogueExplosiveBarrel::ARogueExplosiveBarrel()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	SetRootComponent(StaticMeshComponent);
	StaticMeshComponent->SetSimulatePhysics(true);
	StaticMeshComponent->SetCollisionProfileName("PhysicsActor");
	
	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComp"));
	RadialForceComponent->SetupAttachment(RootComponent);
	RadialForceComponent->bAutoActivate = false;
	RadialForceComponent->bIgnoreOwningActor = true;
	RadialForceComponent->ImpulseStrength = 150000.0f;
	RadialForceComponent->Radius = 800.f;
	
	LoopedAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("LoopedAudioComponent"));
	LoopedAudioComponent->SetupAttachment(StaticMeshComponent);
}

float ARogueExplosiveBarrel::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	class AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	if (!WasHit)
	{
		NiagaraBurningEffectComponent =  UNiagaraFunctionLibrary::SpawnSystemAttached(LoopedBurningEffect, StaticMeshComponent, FName(""), FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget, true);
	
		WasHit = true;
		
		LoopedAudioComponent->Play();
		
		FTimerHandle ExplosionHandle;
		GetWorldTimerManager().SetTimer(ExplosionHandle, this, &ARogueExplosiveBarrel::Explode, ExplosionDelayTime);
	}
	
	return ActualDamage;
}

void ARogueExplosiveBarrel::Explode()
{	
	NiagaraBurningEffectComponent->Deactivate();
	LoopedAudioComponent->Stop();
	
	RadialForceComponent->FireImpulse();
	
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ExplosionEffect, GetActorLocation());
	
	UGameplayStatics::PlaySoundAtLocation(this, ExplosionSound, GetActorLocation());
}


