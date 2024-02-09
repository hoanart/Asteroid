// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectileBase.generated.h"

UCLASS()
class ASTEROID_API AProjectileBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AProjectileBase();

protected:
	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
protected:
	UFUNCTION()
	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,int32 OtherBodyIndex,bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION(BlueprintNativeEvent)
	void Explode();
protected:
	UPROPERTY(VisibleAnywhere,Category = "Components")
	TObjectPtr<class UBoxComponent> BoxComp;
	UPROPERTY(VisibleAnywhere,Category = "Components")
	TObjectPtr<class UParticleSystemComponent> EffectComp;
	UPROPERTY(VisibleAnywhere,Category = "Components")
	TObjectPtr<class UProjectileMovementComponent> MovementComp;

	
};
