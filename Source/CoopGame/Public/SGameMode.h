// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SGameMode.generated.h"


enum class EWaveState : uint8;

//KILLED actor, kiill actor, 
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnActorKilled, AActor*, VictimActor, AActor*, KillerActor,AController*, KillerController);
/**
 * 
 */
UCLASS()
class COOPGAME_API ASGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
protected:

	//Hook for BP to spawn a single bot
	UFUNCTION(BlueprintImplementableEvent, Category="GameMode")
	void SpawnNewBot();

	void SpawnBotTimerElapsed();

	//Start spawn bots
	void StartWave();

	//stop spawn bots
	void EndWave();

	//set timer for next spawn
	void PreparForNextWave();

	void CheckWaveState();

	void CheckAnyPlayerAlive();

	void GameOver();
	
	void SetWaveState(EWaveState NewState);

	void ReStartDeadPlayer();

	FTimerHandle TimerHandle_BotSpawner;

	int32 NumberOfBotsToSpawn;

	int32 WaveCount;

	FTimerHandle TimerHandle_NextWaveStart;

	UPROPERTY(EditAnywhere, Category="GameMode")
	float TimeBetweenWaves;
public:

	ASGameMode();

	virtual void StartPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(BlueprintAssignable,Category="GameMode")
		FOnActorKilled OnActorKilled;
};
