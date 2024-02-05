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
	protected:
	void Move(const FInputActionValue& Value);
	void Turn(const FInputActionValue& Value);
	void Shoot(const FInputActionValue& Value);


	//Property
protected:
	UPROPERTY(VisibleAnywhere,Category="Components")
	TObjectPtr<class UCapsuleComponent> CapsuleComp;
	UPROPERTY(VisibleAnywhere,Category="Components")
	TObjectPtr<class UStaticMeshComponent> MeshComp;
	UPROPERTY(VisibleAnywhere,Category = "Components")
	TObjectPtr<class UCameraComponent> CameraComp;
	UPROPERTY(VisibleAnywhere,Category = "Components")
	TObjectPtr<class USpringArmComponent> SpringArmComp;

	//TObjectPtr<class APlayerController> PlayerController;

protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category = "Input",meta = (AllowPrivateAccess = true))
	TObjectPtr<class UInputMappingContext> DefaultMappingContext;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category = "Input",meta = (AllowPrivateAccess = true))
	TObjectPtr<class UInputAction> MoveAction;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category = "Input",meta = (AllowPrivateAccess = true))
	TObjectPtr<class UInputAction> TurnAction;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category = "Input",meta = (AllowPrivateAccess = true))
	TObjectPtr<class UInputAction> ShootAction;
};
