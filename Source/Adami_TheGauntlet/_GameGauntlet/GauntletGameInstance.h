#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GauntletGameInstance.generated.h"

/**
 * Gestisce il flusso del gioco (Menu -> Gameplay -> Quit)
 * Persiste attraverso i cambi di livello.
 */
UCLASS()
class ADAMI_THEGAUNTLET_API UGauntletGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, Category = "Game Flow")
	FName MainMenuMapName = FName("Lvl_GauntletMainMenu");

	UPROPERTY(EditDefaultsOnly, Category = "Game Flow")
	FName GameplayLevelName = FName("Lvl_GauntletGame");

	UPROPERTY(EditDefaultsOnly, Category = "Game Flow")
	TSoftObjectPtr<UWorld> MainMenuMapWorld;
	
	UPROPERTY(EditDefaultsOnly, Category = "Game Flow")
	TSoftObjectPtr<UWorld> GameplayLevelWorld;

	// --- Funzioni di Flusso ---
    UFUNCTION(BlueprintCallable, Category = "Game Flow")
	void LaunchGame();

	UFUNCTION(BlueprintCallable, Category = "Game Flow")
	void LoadMainMenu();

	UFUNCTION(BlueprintCallable, Category = "Game Flow")
	void QuitGame();
};