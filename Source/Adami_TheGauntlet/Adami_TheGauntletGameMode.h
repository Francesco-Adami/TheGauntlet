// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Adami_TheGauntletGameMode.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameStateChanged);


UCLASS()
class ADAMI_THEGAUNTLET_API AAdami_TheGauntletGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AAdami_TheGauntletGameMode();

	// --- DELEGATI (Eventi a cui la UI si iscrive) ---
	
	UPROPERTY(BlueprintAssignable, Category = "Game Events")
	FOnGameStateChanged OnGameOver;

	UPROPERTY(BlueprintAssignable, Category = "Game Events")
	FOnGameStateChanged OnGameWon;

	// --- FUNZIONI DI STATO (Chiamate da Character e Trigger) ---

	UFUNCTION(BlueprintCallable, Category = "Game Rules")
	void PlayerDied();

	/** Chiamata dalla VictoryZone quando il player arriva alla fine */
	UFUNCTION(BlueprintCallable, Category = "Game Rules")
	void LevelCompleted();

	UFUNCTION(BlueprintCallable, Category = "Game Rules")
	void RestartLevel();
	
	UFUNCTION(BlueprintCallable, Category = "Game Rules")
	void ReturnToMainMenu();

	// Ritardo prima di riavviare o tornare al menu (es. 3 secondi)
	UPROPERTY(EditDefaultsOnly, Category = "Game Rules")
	float RestartDelay = 3.0f;

	// Flag per evitare che il gioco finisca due volte contemporaneamente
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Game Rules")
	bool bIsGameOver = false;
};



