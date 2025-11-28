// Copyright Epic Games, Inc. All Rights Reserved.

#include "Adami_TheGauntletCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Adami_TheGauntlet.h"
#include "Collectible.h"
#include "Damageable.h"
#include "Interactable.h"

AAdami_TheGauntletCharacter::AAdami_TheGauntletCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void AAdami_TheGauntletCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Otteniamo il riferimento alla capsula del personaggio
	UCapsuleComponent* Capsule = GetCapsuleComponent();

	if (Capsule)
	{
		Capsule->OnComponentBeginOverlap.AddDynamic(this, &AAdami_TheGauntletCharacter::OnOverlapBegin);
	}
}

void AAdami_TheGauntletCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 1. Controllo di validità: assicurati che non sia nullo e che non sia il player stesso
	if (OtherActor && (OtherActor != this)) 
	{
		UE_LOG(LogTemp, Log, TEXT("Overlap con: %s"), *OtherActor->GetName());

		if (OtherActor->Implements<UCollectible>())
		{
			ICollectible::Execute_OnCollect(OtherActor, this);
		}
	}
}

void AAdami_TheGauntletCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAdami_TheGauntletCharacter::Move);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &AAdami_TheGauntletCharacter::Look);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AAdami_TheGauntletCharacter::Look);
	}
	else
	{
		UE_LOG(LogAdami_TheGauntlet, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AAdami_TheGauntletCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	// route the input
	DoMove(MovementVector.X, MovementVector.Y);
}

void AAdami_TheGauntletCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// route the input
	DoLook(LookAxisVector.X, LookAxisVector.Y);
}

void AAdami_TheGauntletCharacter::DoMove(float Right, float Forward)
{
	if (GetController() != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, Forward);
		AddMovementInput(RightDirection, Right);
	}
}

void AAdami_TheGauntletCharacter::DoLook(float Yaw, float Pitch)
{
	if (GetController() != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void AAdami_TheGauntletCharacter::DoJumpStart()
{
	// signal the character to jump
	Jump();
}

void AAdami_TheGauntletCharacter::DoJumpEnd()
{
	// signal the character to stop jumping
	StopJumping();
}

void AAdami_TheGauntletCharacter::DoFire()
{
	FHitResult Hit;
	FVector StartLocation = FollowCamera->GetComponentLocation();
	FVector ForwardVector = FollowCamera->GetForwardVector();
	const float TraceDistance = 1000.0f; 
	FVector EndLocation = StartLocation + (ForwardVector * TraceDistance);

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
    
	// --- Esecuzione del Line Trace ---
	if (GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, EndLocation, ECC_Visibility, Params))
	{
		AActor* HitActor = Hit.GetActor();
       
		if (HitActor && HitActor->Implements<UDamageable>())
		{
			IDamageable::Execute_TakeDamage(HitActor, 25.0f);
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("Colpito: %s"), *HitActor->GetName()));
		}
	}
}

void AAdami_TheGauntletCharacter::DoInteract()
{
	FHitResult Hit;
	FVector StartLocation = FollowCamera->GetComponentLocation();
	FVector ForwardVector = FollowCamera->GetForwardVector();
	const float TraceDistance = 1000.0f; 
	FVector EndLocation = StartLocation + (ForwardVector * TraceDistance);

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
    
	// --- Esecuzione del Line Trace ---
	if (GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, EndLocation, ECC_Visibility, Params))
	{
		AActor* HitActor = Hit.GetActor();
       
		if (HitActor && HitActor->Implements<UInteractable>())
		{
			IInteractable::Execute_Interact(HitActor, this);
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("Interacted: %s"), *HitActor->GetName()));
			// DrawDebugLine(GetWorld(), StartLocation, EndLocation, HitActor ? FColor::Green : FColor::Red, false, 2.0f, 0, 2.0f);
		}
	}

}
