// Copyright Epic Games, Inc. All Rights Reserved.

#include "Adami_TheGauntletGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "_GameGauntlet/GauntletGameInstance.h"

AAdami_TheGauntletGameMode::AAdami_TheGauntletGameMode()
{
}

void AAdami_TheGauntletGameMode::PlayerDied()
{
	if (bIsGameOver) return;
	
	bIsGameOver = true;

	if (OnGameOver.IsBound())
	{
		OnGameOver.Broadcast();
	}

	UE_LOG(LogTemp, Warning, TEXT("GAME OVER: Player Defeated."));
}

void AAdami_TheGauntletGameMode::LevelCompleted()
{
	if (bIsGameOver) return;

	bIsGameOver = true;

	if (OnGameWon.IsBound())
	{
		OnGameWon.Broadcast();
	}

	UE_LOG(LogTemp, Log, TEXT("VICTORY: Level Completed. Returning to Menu..."));

	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC)
	{
		PC->GetPawn()->DisableInput(PC);
	}
}

void AAdami_TheGauntletGameMode::RestartLevel()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

void AAdami_TheGauntletGameMode::ReturnToMainMenu()
{
	UGauntletGameInstance* GI = Cast<UGauntletGameInstance>(GetGameInstance());
	
	if (GI)
	{
		UE_LOG(LogTemp, Error, TEXT("LOADING MAIN MENU"));
		GI->LoadMainMenu();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("GameInstance non trovata o cast fallito!"));
		UGameplayStatics::OpenLevel(this, FName("MainMenu"));
	}
}
