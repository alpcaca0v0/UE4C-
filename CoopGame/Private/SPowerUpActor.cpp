// Fill out your copyright notice in the Description page of Project Settings.


#include "SPowerUpActor.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ASPowerUpActor::ASPowerUpActor()
{
	PowerUpInterval = 0.0f;

	TotalNrOfTicks = 0.0f;

	SetReplicates(true);

	bIsPowerUpActive = false;
}

void ASPowerUpActor::OnTickPowerUp()
{
	TickProcessed++;

	OnPowerUpTicked();

	if (TickProcessed >= TotalNrOfTicks)
	{
		OnExpired();

		bIsPowerUpActive = false;
		OnRep_PowerUpActive();

		//clear Timer
		GetWorldTimerManager().ClearTimer(TimerHandle_PowerUpTicks);
	}
}

void ASPowerUpActor::OnRep_PowerUpActive()
{
	OnPowerUpActiveChanged(bIsPowerUpActive);
}

void ASPowerUpActor::ActivatePowerUp(AActor* ActiveFor)
{
	OnActivated(ActiveFor);

	bIsPowerUpActive = true;
	OnRep_PowerUpActive();

	if (PowerUpInterval > 0.0f)
	{
		GetWorldTimerManager().SetTimer(TimerHandle_PowerUpTicks, this,
			&ASPowerUpActor::OnTickPowerUp, PowerUpInterval, true);
	}
	else
	{
		OnTickPowerUp();
	}
}

void ASPowerUpActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASPowerUpActor, bIsPowerUpActive);
}
