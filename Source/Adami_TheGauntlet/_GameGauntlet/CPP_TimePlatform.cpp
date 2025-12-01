// Fill out your copyright notice in the Description page of Project Settings.


#include "_GameGauntlet/CPP_TimePlatform.h"

#include "CPP_TimeButton.h"

// Sets default values
ACPP_TimePlatform::ACPP_TimePlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ACPP_TimePlatform::BeginPlay()
{
	Super::BeginPlay();

	if (LinkedButton)
	{
		LinkedButton->OnPressedDynamic.AddDynamic(this, &ACPP_TimePlatform::ActivatePlatform);
	}

	IsActive = false;
	DeactivatePlatform();
}

// Called every frame
// void ACPP_TimePlatform::Tick(float DeltaTime)
// {
// 	Super::Tick(DeltaTime);
//
// 	if (IsActive)
// 	{
// 		TimeElapsed += DeltaTime;
// 		if (TimeElapsed >= TimeDuration)
// 		{
// 			DeactivatePlatform();
// 		}
// 	}
// }

void ACPP_TimePlatform::ActivatePlatform()
{
	if (IsActive) return;
	
	// IsActive = true;

	// ...
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);

	GEngine->AddOnScreenDebugMessage(
		-1,
		5.0f,
		FColor::Magenta,
		"ACTIVATED PLATFORM"
	);

	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle_Platform,                   // Handle per rintracciare questo timer
		this,                                   // Chi chiama la funzione? (this)
		&ACPP_TimePlatform::DeactivatePlatform, // Quale funzione chiamare allo scadere?
		TimeDuration,                           // Tra quanti secondi?
		false                                   // Loop? False = una volta sola
	);
}

void ACPP_TimePlatform::DeactivatePlatform()
{
	// ...
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);

	
	GEngine->AddOnScreenDebugMessage(
		-1,
		4.0f,
		FColor::Red,
		"DEACTIVATED PLATFORM"
	);

	GetWorld()->GetTimerManager().ClearTimer(TimerHandle_Platform);

	// Reset
	// IsActive = false;
	// TimeElapsed = 0;
}

