// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeComponent.h"

// Sets default values for this component's properties
UAttributeComponent::UAttributeComponent(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{

	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	HealthMax = 5;
	 Health = 5;
	// ...
}


UAttributeComponent* UAttributeComponent::GetAttributes(AActor* FromActor)
{
	if(!IsValid(FromActor))
	{
		return nullptr;
	}
	return FromActor->FindComponentByClass<UAttributeComponent>();
}


// Called when the game starts
void UAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UAttributeComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	if(PropertyChangedEvent.GetPropertyName()== GET_MEMBER_NAME_CHECKED(UAttributeComponent, HealthMax))
	{
		Health =HealthMax;
	}
}


// Called every frame
void UAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

const float& UAttributeComponent::GetHealth() const
{
	return Health;
}

bool UAttributeComponent::IsAlive() const
{
	return Health>0;
}

bool UAttributeComponent::ApplyHealthChange(float Delta)
{
	float OldHealth = Health;
	Health  = FMath::Clamp(Delta+Health,0,HealthMax);

	float ActualDelta = Health-OldHealth;

	OnHealthChanged.Broadcast(nullptr,this,Health,ActualDelta);
	return ActualDelta!=0;
}



