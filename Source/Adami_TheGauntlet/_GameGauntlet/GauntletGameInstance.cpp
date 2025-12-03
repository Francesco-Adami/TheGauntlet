

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
	// UGameplayStatics::OpenLevel(this, GameplayLevelName);
	UGameplayStatics::OpenLevelBySoftObjectPtr( GetWorld(), GameplayLevelWorld);
	UE_LOG(LogTemp, Log, TEXT("Avvio del gioco: Caricamento %s"), *GameplayLevelName.ToString());
}

void UGauntletGameInstance::LoadMainMenu()
{
	if (MainMenuMapName.IsNone()) return;

	UE_LOG(LogTemp, Error, TEXT("MainMenuMapName: %s"), *MainMenuMapName.ToString());
	// UGameplayStatics::OpenLevel(this, MainMenuMapName);
	UGameplayStatics::OpenLevelBySoftObjectPtr( GetWorld(), MainMenuMapWorld);
}

void UGauntletGameInstance::QuitGame()
{
	APlayerController* PC = GetFirstLocalPlayerController();
	
	if (PC)
	{
		UKismetSystemLibrary::QuitGame(GetWorld(), PC, EQuitPreference::Quit, true);
		UE_LOG(LogTemp, Log, TEXT("Richiesta chiusura gioco inviata."));
	}
}

