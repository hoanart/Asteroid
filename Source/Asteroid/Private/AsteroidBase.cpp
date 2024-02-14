// Fill out your copyright notice in the Description page of Project Settings.


#include "AsteroidBase.h"

#include "AttributeComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AAsteroidBase::AAsteroidBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	RootComponent = SphereComp;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	Mesh->SetupAttachment(RootComponent);

	AttributeComp = CreateDefaultSubobject<UAttributeComponent>("AttributeComp");
	
}

void AAsteroidBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AttributeComp->OnHealthChanged.AddDynamic(this,&AAsteroidBase::OnHealthChanged);
}

// Called when the game starts or when spawned
void AAsteroidBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAsteroidBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAsteroidBase::OnHealthChanged(AActor* InstigatorActor, UAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	if(NewHealth<=0&&Delta<0.0f)
	{
		Destroy();
	}
}

