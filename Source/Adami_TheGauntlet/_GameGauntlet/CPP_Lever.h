// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "GameFramework/Actor.h"
#include "CPP_Lever.generated.h"

class ACPP_FinalGate;

UCLASS()
class ADAMI_THEGAUNTLET_API ACPP_Lever : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_Lever();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* MeshComp;

	UPROPERTY()
	UMaterialInstanceDynamic* LeverMaterialInst;

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Final Lever")
	int LeverIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Final Lever")
	ACPP_FinalGate* LinkedGate;

	virtual void Interact_Implementation(AActor* Interactor) override;

};
