// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"

#include "AttributeComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectileBase::AProjectileBase()
	:DamageAmount(1.0f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxComp = CreateDefaultSubobject<UBoxComponent>("BoxComp");
	RootComponent = BoxComp;

	EffectComp=CreateDefaultSubobject<UParticleSystemComponent>("ParticleComp");
	EffectComp->SetupAttachment(RootComponent);
	
	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->InitialSpeed = 8000.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;
}

void AProjectileBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
}


// Called every frame
void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AProjectileBase::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//UE_LOG(LogTemp,Display,TEXT("Overlap : %s, %s"), *StaticClass()->GetName(),*GetClass()->GetName());
	if(GetInstigator()!=OtherActor  )
	{
		UE_LOG(LogTemp,Display,TEXT("OtherActor1 : %s, %s"), *OtherActor->StaticClass()->GetName(),*OtherActor->GetClass()->GetName());

		//OtherActor : Staticclass = Actor GetClass = BP_Bullet
		if(GetClass()==OtherActor->GetClass())
		{
			return;
		}

		TObjectPtr<UAttributeComponent> AttributeComp = Cast<UAttributeComponent>(UAttributeComponent::GetAttributes(OtherActor));
		if(IsValid(AttributeComp))
		{
			UE_LOG(LogTemp,Display,TEXT("OtherActor2 : %s, %s"), *OtherActor->StaticClass()->GetName(),*OtherActor->GetClass()->GetName());
			AttributeComp->ApplyHealthChange(-DamageAmount);	
			Explode();	
		}
		
	}
}

void AProjectileBase::Explode_Implementation()
{
	if(ensure(BoxComp))
	{
		EffectComp->DeactivateSystem();
		MovementComp->StopMovementImmediately();

		SetActorEnableCollision(false);
		FString CombinedString = FString::Printf(TEXT("Collision"));
		GEngine->AddOnScreenDebugMessage(-1,0.2f,FColor::Green,CombinedString);
		Destroy();
	}
}

