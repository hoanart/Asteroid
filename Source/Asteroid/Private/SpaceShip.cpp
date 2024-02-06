// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShip.h"

#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/InputComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASpaceShip::ASpaceShip()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	MeshComp->SetupAttachment(RootComponent);
	RootComponent= MeshComp;
	
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->SetupAttachment(RootComponent);
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	FloatingMovementComp = CreateDefaultSubobject<UFloatingPawnMovement>("FloatingMovementComp");
	FloatingMovementComp->MaxSpeed = 700.0f;
	
}

void ASpaceShip::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

// Called when the game starts or when spawned
void ASpaceShip::BeginPlay()
{
	Super::BeginPlay();
	if(TObjectPtr<APlayerController> PlayerController = CastChecked<APlayerController>(Controller))
	{
		if(TObjectPtr<UEnhancedInputLocalPlayerSubsystem> Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext,0);
		}
	}
}

// Called every frame
void ASpaceShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASpaceShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if(TObjectPtr<UEnhancedInputComponent> EnhancedInputComp = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		
		EnhancedInputComp->BindAction(MoveAction,ETriggerEvent::Triggered,this,&ASpaceShip::Move);
		EnhancedInputComp->BindAction(TurnAction,ETriggerEvent::Triggered,this,&ASpaceShip::Turn);
		EnhancedInputComp->BindAction(ShootAction,ETriggerEvent::Triggered,this,&ASpaceShip::Shoot);
	}
	
}

void ASpaceShip::Move(const FInputActionValue& Value)
{
	
	// FString CombinedString = FString::Printf(TEXT("VALUE : %f"),Value.Get<float>());
	// GEngine->AddOnScreenDebugMessage(-1,2.f,FColor::Green,CombinedString);
	// float Speed =  Value.Get<float>()* 10000.0f;
	//
	// FVector ForceVec = MeshComp->GetForwardVector()*Speed;
	//
	// MeshComp->AddForce(ForceVec,NAME_None,true);
	//
	FVector2d MovementVec = Value.Get<FVector2D>();

	if(IsValid(Controller))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRot(0,Rotation.Yaw,0);

		const FVector ForwardDir = FRotationMatrix(YawRot).GetUnitAxis(EAxis::X);
		const FVector RightDir = FRotationMatrix(YawRot).GetUnitAxis(EAxis::Y);
		float Speed = 10000.0f;
		 FString CombinedString = FString::Printf(TEXT("VALUE : %s"),*ForwardDir.ToString());
		 GEngine->AddOnScreenDebugMessage(-1,0.5f,FColor::Green,CombinedString);
		FVector ForceVec = ForwardDir*MovementVec.Y*Speed;

		AddMovementInput(ForwardDir,MovementVec.Y);
		AddMovementInput(RightDir,MovementVec.X);
		
		
		
	}
}

void ASpaceShip::Turn(const FInputActionValue& Value)
{
}

void ASpaceShip::Shoot(const FInputActionValue& Value)
{
	
}

