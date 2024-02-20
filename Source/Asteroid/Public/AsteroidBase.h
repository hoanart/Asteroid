// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AsteroidBase.generated.h"

UCLASS()
class ASTEROID_API AAsteroidBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAsteroidBase();

protected:
	virtual void PostInitializeComponents() override;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor,class UAttributeComponent* OwningComp,float NewHealth, float Delta);
	UFUNCTION()
	void OnOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	void OnHit(class UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
protected:
	UPROPERTY(VisibleAnywhere,Category = "Components")
	TObjectPtr<class UStaticMeshComponent> Mesh;
	
	 UPROPERTY(VisibleAnywhere,Category = "Components")
	TObjectPtr<class UAttributeComponent> AttributeComp;
	
	UPROPERTY(VisibleAnywhere,Category = "Components")
	TObjectPtr<class UProjectileMovementComponent> MovementComp;

	UPROPERTY(VisibleAnywhere,Category = "Components")
	TObjectPtr<class UArrowComponent> ArrowComp;
private:
	FTimerHandle CollisionTimer;
	bool bDoOnce;
};
