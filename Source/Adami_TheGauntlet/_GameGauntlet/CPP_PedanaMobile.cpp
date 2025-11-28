// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_PedanaMobile.h"

// Sets default values
ACPP_PedanaMobile::ACPP_PedanaMobile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootAnchor"));

	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformMesh"));
	PlatformMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ACPP_PedanaMobile::BeginPlay()
{
	Super::BeginPlay();
	
	// Controllo sicurezza
	if (WayPoints.Num() == 0 || !PlatformMesh) return;

	PlatformMesh->SetRelativeLocation(WayPoints[0].GetLocation());

	IndexWayPoint = 0;
	StartPosition = WayPoints[0].GetLocation();
    
	// Il primo target sarà il punto 1 (se esiste), altrimenti rimane 0
	int NextIndex = (IndexWayPoint + 1) % WayPoints.Num();
	TargetPosition = WayPoints[NextIndex].GetLocation();
}

// Called every frame
void ACPP_PedanaMobile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Move(DeltaTime);
}

void ACPP_PedanaMobile::Move(float DeltaTime)
{
	if (WayPoints.Num() < 2 || !PlatformMesh) return;

	PercentageCompleted += DeltaTime / Speed;
	
	FVector NewRelativeLocation = FMath::Lerp(StartPosition, TargetPosition, PercentageCompleted);
	
	PlatformMesh->SetRelativeLocation(NewRelativeLocation);

	if (PercentageCompleted >= 1.0f)
	{
		IndexWayPoint = (IndexWayPoint + 1) % WayPoints.Num();
        
		StartPosition = TargetPosition; 

		int NextIndex = (IndexWayPoint + 1) % WayPoints.Num();
		TargetPosition = WayPoints[NextIndex].GetLocation();

		PercentageCompleted = 0.0f;
	}
}

