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
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UFUNCTION(BlueprintGetter)
	const float& GetHealth() const;
	UFUNCTION(BlueprintGetter)
	const int& GetScore() const;
public:
	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;
	
public:
	UFUNCTION(BlueprintCallable)
	bool ApplyHealthChange(float Delta);
	UFUNCTION(BlueprintPure,Category="Health")
	bool IsAlive() const;

	
protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Attributes")
	float HealthMax;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,BlueprintGetter= "GetHealth", Category = "Attributes")
	float Health;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,BlueprintGetter= "GetScore", Category = "Attributes")
	int Score;
};
