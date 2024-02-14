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
protected:
	UPROPERTY(VisibleAnywhere,Category = "Components")
	TObjectPtr<class USphereComponent> SphereComp;
	UPROPERTY(VisibleAnywhere,Category = "Components")
	TObjectPtr<class UStaticMeshComponent> Mesh;
	UPROPERTY(VisibleAnywhere,Category = "Components")
	TObjectPtr<class UAttributeComponent> AttributeComp;

protected:
};
