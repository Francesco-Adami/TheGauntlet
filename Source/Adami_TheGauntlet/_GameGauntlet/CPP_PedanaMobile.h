// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_PedanaMobile.generated.h"

UCLASS()
class ADAMI_THEGAUNTLET_API ACPP_PedanaMobile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_PedanaMobile();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pedana", meta = (MakeEditWidget = true))
	TArray<FTransform> WayPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pedana")
	float Speed = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pedana")
	UStaticMeshComponent* PlatformMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	int IndexWayPoint = 0;
	float PercentageCompleted = 0.0f;

	FVector StartPosition;
	FVector TargetPosition;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Move(float DeltaTime);

};
