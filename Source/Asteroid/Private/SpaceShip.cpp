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
	:RotateRate(1.0f)
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
		PlayerController->SetShowMouseCursor(true);
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
	FVector Loc = GetActorLocation();
	FHitResult Hit;

	UGameplayStatics::GetPlayerController(GetWorld(),0)->GetHitResultUnderCursor(ECC_Visibility,true,Hit);

	FVector Dir = Hit.Location - Loc;
	FRotator Rot = FRotationMatrix::MakeFromX(Dir).Rotator();
	SetActorRotation(FMath::RInterpTo(MeshComp->GetComponentRotation(),FRotator(0.f,Rot.Yaw,0.f),DeltaTime,RotateRate));
	//AddActorWorldRotation(FMath::RInterpTo(MeshComp->GetComponentRotation(),FRotator(0.f,Rot.Yaw,0.f),DeltaTime,5000.0f),true);
	//MeshComp->SetWorldRotation(FMath::RInterpTo(MeshComp->GetComponentRotation(),FRotator(0.f,Rot.Yaw,0.f),DeltaTime,10.0f));
	Controller->SetControlRotation(MeshComp->GetComponentRotation());
	
}

// Called to bind functionality to input
void ASpaceShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if(TObjectPtr<UEnhancedInputComponent> EnhancedInputComp = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		
		EnhancedInputComp->BindAction(MoveAction,ETriggerEvent::Triggered,this,&ASpaceShip::Move);
		EnhancedInputComp->BindAction(ShootAction,ETriggerEvent::Triggered,this,&ASpaceShip::Shoot);
	}
}

void ASpaceShip::Move(const FInputActionValue& Value)
{
	FVector2d MovementVec = Value.Get<FVector2D>();

	if(IsValid(Controller))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRot(0,Rotation.Yaw,0);

		const FVector ForwardDir = FRotationMatrix(YawRot).GetUnitAxis(EAxis::X);
		const FVector RightDir = FRotationMatrix(YawRot).GetUnitAxis(EAxis::Y);
		float Speed = 10000.0f;
		 FString CombinedString = FString::Printf(TEXT("VALUE : %s"),*MovementVec.ToString());
		 GEngine->AddOnScreenDebugMessage(-1,0.2f,FColor::Green,CombinedString);
		FVector ForceVec = ForwardDir*MovementVec.Y*Speed;

		
		AddMovementInput(ForwardDir,MovementVec.Y);
		AddMovementInput(RightDir,MovementVec.X);
	}
}


void ASpaceShip::Shoot(const FInputActionValue& Value)
{
		
	UE_LOG(LogTemp,Display,TEXT("Shoot : %d"),Value.Get<bool>());
	FCannonSockets CannonSockets;

	FVector CannonLoc1 = MeshComp->GetSocketLocation(CannonSockets.Socket1);
	FVector CannonLoc2 = MeshComp->GetSocketLocation(CannonSockets.Socket2);
	DrawDebugSphere(GetWorld(),CannonLoc1,500.0f,10.0f,FColor::Green,true,-1,0,4.f);
	
	FString CombinedString = FString::Printf(TEXT("VALUE : %s"),*CannonLoc1.ToString());
	GEngine->AddOnScreenDebugMessage(-1,0.2f,FColor::Green,CombinedString);
	FRotator Rot = FRotationMatrix::MakeFromX(CannonLoc1).Rotator();
	
	FTransform SpawnTM = FTransform(MeshComp->GetSocketRotation(CannonSockets.Socket1),CannonLoc1);
	FTransform SpawnTM2 = FTransform(MeshComp->GetSocketRotation(CannonSockets.Socket2),CannonLoc2);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;

	GetWorld()->SpawnActor<AActor>(ProjectileClass,SpawnTM,SpawnParams);
	GetWorld()->SpawnActor<AActor>(ProjectileClass,SpawnTM2,SpawnParams);
}

