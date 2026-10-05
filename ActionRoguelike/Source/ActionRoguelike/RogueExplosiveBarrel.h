// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RogueExplosiveBarrel.generated.h"

class URadialForceComponent;
class UNiagaraComponent;
class UNiagaraSystem;
class UStaticMeshComponent;
class UAudioComponent;
class USoundBase;
UCLASS()
class ACTIONROGUELIKE_API ARogueExplosiveBarrel : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARogueExplosiveBarrel();

protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	TObjectPtr<UNiagaraSystem> LoopedBurningEffect;
	
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	TObjectPtr<UNiagaraSystem> ExplosionEffect;
	
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	TObjectPtr<USoundBase> ExplosionSound;
	
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	float ExplosionDelayTime = 3.0f;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UAudioComponent> LoopedAudioComponent;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<URadialForceComponent> RadialForceComponent;
	
	
	float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	
	void Explode();
	
	UNiagaraComponent* NiagaraBurningEffectComponent;
	
	bool WasHit;
};
