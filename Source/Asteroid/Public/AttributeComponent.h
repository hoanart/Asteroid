// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged,AActor*,InstigatorActor,UAttributeComponent*,OwningComp,float,NewHealth,float,Delta);
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ASTEROID_API UAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAttributeComponent();
	UFUNCTION()
	static UAttributeComponent* GetAttributes(AActor* FromActor);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	bool ApplyHealthChange(float Delta);

public:
	FOnHealthChanged OnHealthChanged;
	
protected:
	UPROPERTY(EditDefaultsOnly,Category = "Attributes")
	float HealthMax;
	UPROPERTY(VisibleAnywhere,Category = "Attributes")
	float Health;
	
		
};
