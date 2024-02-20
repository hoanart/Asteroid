// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "SpaceShip.generated.h"

UCLASS()
class ASTEROID_API ASpaceShip : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASpaceShip();

protected:
	virtual void PostInitializeComponents() override;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
		
	//Method
public:
	void StartHitStop(FVector NormalImpulse);
	protected:
	void Move(const FInputActionValue& Value);
	void Shoot(const FInputActionValue& Value);

protected:
	
	void StopHitStop();
	//Property
protected:
	UPROPERTY(EditAnywhere,Category = "Rotation")
	float RotateRate;
	UPROPERTY(EditAnywhere,Category = "Collision")
	float ImpulseStrength;
protected:
	UPROPERTY(EditAnywhere,Category = "Projectile")
	TSubclassOf<AActor> ProjectileClass;
protected:
	UPROPERTY(VisibleAnywhere,Category="Components")
	TObjectPtr<class UCapsuleComponent> CapsuleComp;
	UPROPERTY(VisibleAnywhere,Category="Components")
	TObjectPtr<class UStaticMeshComponent> MeshComp;
	UPROPERTY(VisibleAnywhere,Category = "Components")
	TObjectPtr<class UCameraComponent> CameraComp;
	UPROPERTY(VisibleAnywhere,Category = "Components")
	TObjectPtr<class USpringArmComponent> SpringArmComp;
	UPROPERTY(VisibleAnywhere,Category = "Components")
	TObjectPtr<class UFloatingPawnMovement> FloatingMovementComp;
	UPROPERTY(VisibleAnywhere,Category = "Components")
	TObjectPtr<class UAttributeComponent> AttributeComp;
	//TObjectPtr<class APlayerController> PlayerController;

protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category = "Input",meta = (AllowPrivateAccess = true))
	TObjectPtr<class UInputMappingContext> DefaultMappingContext;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category = "Input",meta = (AllowPrivateAccess = true))
	TObjectPtr<class UInputAction> MoveAction;
	

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category = "Input",meta = (AllowPrivateAccess = true))
	TObjectPtr<class UInputAction> ShootAction;

private:
	FTimerHandle StopHitTimer;
};

USTRUCT(BlueprintType)
struct FCannonSockets
{
	GENERATED_BODY()
	UPROPERTY( BlueprintReadOnly)
	FName Socket1;
	UPROPERTY(BlueprintReadOnly)
	FName Socket2;
	FCannonSockets()
	{
		Socket1 = "cannon1";
		Socket2 = "cannon2";
	}
};
