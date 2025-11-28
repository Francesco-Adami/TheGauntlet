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
	// --- Nomi dei Livelli (Configurabili da Editor) ---
	
	UPROPERTY(EditDefaultsOnly, Category = "Game Flow")
	FName MainMenuMapName = FName("MainMenu");

	UPROPERTY(EditDefaultsOnly, Category = "Game Flow")
	FName GameplayLevelName = FName("Level_01");

	// --- Funzioni di Flusso (Richieste dal Progetto) ---

	/** Carica il livello di gioco principale (Start Game) */
	UFUNCTION(BlueprintCallable, Category = "Game Flow")
	void LaunchGame();

	/** Torna al Menu Principale */
	UFUNCTION(BlueprintCallable, Category = "Game Flow")
	void LoadMainMenu();

	/** Chiude l'applicazione */
	UFUNCTION(BlueprintCallable, Category = "Game Flow")
	void QuitGame();
};