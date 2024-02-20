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
	UFUNCTION()
	static UAttributeComponent* GetAttributes(AActor* FromActor);
	// Sets default values for this component's properties
	UAttributeComponent(const FObjectInitializer& ObjectInitializer);
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
public:
	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;
	
public:
	UFUNCTION(BlueprintCallable)
	bool ApplyHealthChange(float Delta);


	
protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Attributes")
	float HealthMax;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Attributes")
	float Health;
	
		
};
