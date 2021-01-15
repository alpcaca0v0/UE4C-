// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "STrack.generated.h"

class UStaticMeshComponent;
class USHealthComponent;
class USphereComponent;
class USoundCue;

UCLASS()
class COOPGAME_API ASTrack : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASTrack();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	USHealthComponent* HealthComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	USphereComponent* SphereComp;


	UFUNCTION()
	void HandleTakeDamage(USHealthComponent* OwningHealthComp, float Health, float HealthDelta,
		const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	FVector GetNextPathPoint();

	FVector NextPathPoint;

	UPROPERTY(EditDefaultsOnly, Category="TracerBot")
	float MovementForce;

	UPROPERTY(EditDefaultsOnly, Category = "TracerBot")
	bool bUseVelocityChange;

	UPROPERTY(EditDefaultsOnly, Category = "TracerBot")
	float RequireDistanceToTarget;

	//受伤害后的闪光
	UMaterialInstanceDynamic* MatInst;


	void SelfDestruct();

	UPROPERTY(EditDefaultsOnly, Category = "TracerBot")
	UParticleSystem* ExplosionEffect;

	bool bExploded;

	UPROPERTY(EditDefaultsOnly, Category = "TracerBot")
	float ExplosionRadius;

	UPROPERTY(EditDefaultsOnly, Category = "TracerBot")
	float ExplosionDamage;

	UPROPERTY(EditDefaultsOnly, Category = "TracerBot")
	float SelfDamageInterval;

	UPROPERTY(EditDefaultsOnly, Category = "TracerBot")
	float SelfDamage;

	FTimerHandle TimerHandle_SelfDamage;

	void DamageSelf();

	UPROPERTY(EditDefaultsOnly, Category = "TracerBot")
	USoundCue* SelfDestructSound;

	UPROPERTY(EditDefaultsOnly, Category = "TracerBot")
	USoundCue* ExplodeSound;

	void OnCheckNearbyBots();

	int32  PowerLevel;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	FTimerHandle TimerHandle_RefreshPath;

	void RefreshPath();
};
