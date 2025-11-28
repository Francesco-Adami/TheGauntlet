// Fill out your copyright notice in the Description page of Project Settings.


#include "_GameGauntlet/CPP_Lever.h"

#include "CPP_FinalGate.h"

// Sets default values
ACPP_Lever::ACPP_Lever()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Creazione Mesh
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;
}

// Called when the game starts or when spawned
void ACPP_Lever::BeginPlay()
{
	Super::BeginPlay();

	if (MeshComp)
	{
		LeverMaterialInst = MeshComp->CreateAndSetMaterialInstanceDynamic(0);

		if (LeverMaterialInst)
		{
			LeverMaterialInst->SetVectorParameterValue(TEXT("Color"), FLinearColor::Red);
		}
	}
}

void ACPP_Lever::Interact_Implementation(AActor* Interactor)
{
	if (LinkedGate)
	{
		if (LinkedGate->LeversActivated.IsValidIndex(LeverIndex))
		{
			LinkedGate->LeversActivated[LeverIndex] = !LinkedGate->LeversActivated[LeverIndex];
			
			bool bIsNowActive = LinkedGate->LeversActivated[LeverIndex];

			if (LeverMaterialInst)
			{
				if (bIsNowActive)
				{
					// Set Color -> Green
					LeverMaterialInst->SetVectorParameterValue(TEXT("Color"), FLinearColor::Green);
				}
				else
				{
					// Set Color -> Red
					LeverMaterialInst->SetVectorParameterValue(TEXT("Color"), FLinearColor::Red);
				}
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ERRORE: Nessun LinkedGate assegnato alla Leva!"));
	}
}

