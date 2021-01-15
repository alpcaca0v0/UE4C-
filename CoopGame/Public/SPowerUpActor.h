// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SPowerUpActor.generated.h"

UCLASS()
class COOPGAME_API ASPowerUpActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASPowerUpActor();

protected:

	//insist time
	UPROPERTY(EditDefaultsOnly, Category = "PowerUps")
	float PowerUpInterval;

	//apply how many times
	UPROPERTY(EditDefaultsOnly, Category = "PowerUps")
	int32 TotalNrOfTicks;

	//have applyed times
	int32 TickProcessed;

	FTimerHandle TimerHandle_PowerUpTicks;

	UFUNCTION()
	void OnTickPowerUp();

	UPROPERTY(ReplicatedUsing=OnRep_PowerUpActive)
	bool bIsPowerUpActive;

	UFUNCTION()
	void OnRep_PowerUpActive();

	UFUNCTION(BlueprintImplementableEvent, Category = "PowerUps")
	void OnPowerUpActiveChanged(bool bNewIsActive);
public:	

	UFUNCTION(BlueprintImplementableEvent, Category="PowerUps")
	void OnActivated(AActor* ActiveFor);

	UFUNCTION(BlueprintImplementableEvent, Category = "PowerUps")
	void OnExpired();

	UFUNCTION(BlueprintImplementableEvent, Category = "PowerUps")
	void OnPowerUpTicked();

	void ActivatePowerUp(AActor* ActiveFor);
};
