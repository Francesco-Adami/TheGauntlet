// Fill out your copyright notice in the Description page of Project Settings.


#include "_GameGauntlet/CPP_DamageableActor.h"

// Sets default values
ACPP_DamageableActor::ACPP_DamageableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;
}

// Called when the game starts or when spawned
void ACPP_DamageableActor::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;

	if (MeshComp)
	{
		DestroyableMaterialInst = MeshComp->CreateAndSetMaterialInstanceDynamic(0);

		if (DestroyableMaterialInst)
		{
			DestroyableMaterialInst->SetVectorParameterValue(TEXT("Color"), FLinearColor::White);
		}
	}
}

// Called every frame
void ACPP_DamageableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPP_DamageableActor::TakeDamage_Implementation(float DamageAmount)
{
	UE_LOG(LogTemp, Warning, TEXT("DamageableActor::TakeDamage_Implementation"));

	CurrentHealth -= DamageAmount;
	if (CurrentHealth <= 0)
	{
		Destroy();
	}

	if (DestroyableMaterialInst)
	{
		// Set Color -> Green
		float RedValue = CurrentHealth / MaxHealth;
		float GreenValue = RedValue == 1 ? 1 : 0;
		float BlueValue = RedValue == 1 ? 1 : 0;
		DestroyableMaterialInst->SetVectorParameterValue(TEXT("Color"), FLinearColor(RedValue,GreenValue,BlueValue,1));
	}
}

