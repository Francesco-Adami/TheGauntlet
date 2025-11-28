

#include "GauntletGameInstance.h"
#include "Kismet/GameplayStatics.h" 
#include "Kismet/KismetSystemLibrary.h"

void UGauntletGameInstance::LaunchGame()
{
	if (GameplayLevelName.IsNone())
	{
		UE_LOG(LogTemp, Error, TEXT("Nessun nome livello Gameplay impostato nella GameInstance!"));
		return;
	}

	// Carica il livello
	UGameplayStatics::OpenLevel(this, GameplayLevelName);
	UE_LOG(LogTemp, Log, TEXT("Avvio del gioco: Caricamento %s"), *GameplayLevelName.ToString());
}

void UGauntletGameInstance::LoadMainMenu()
{
	if (MainMenuMapName.IsNone()) return;

	UGameplayStatics::OpenLevel(this, MainMenuMapName);
}

void UGauntletGameInstance::QuitGame()
{
	APlayerController* PC = GetFirstLocalPlayerController();
	
	if (PC)
	{
		UKismetSystemLibrary::QuitGame(this, PC, EQuitPreference::Quit, false);
		UE_LOG(LogTemp, Log, TEXT("Richiesta chiusura gioco inviata."));
	}
}