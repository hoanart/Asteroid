// Fill out your copyright notice in the Description page of Project Settings.


#include "AsteroidBase.h"

#include "AttributeComponent.h"
#include "SpaceShip.h"
#include "Components/ArrowComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/MovementComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AAsteroidBase::AAsteroidBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	Mesh->GetBodyInstance()->bLockZTranslation = true;
	Mesh->SetEnableGravity(false);
	Mesh->SetCollisionProfileName("Asteroid");
	Mesh->SetNotifyRigidBodyCollision(true);
	RootComponent = Mesh;

	AttributeComp = CreateDefaultSubobject<UAttributeComponent>("AttributeComp");
	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->ProjectileGravityScale = 0.f;
	
	ArrowComp = CreateDefaultSubobject<UArrowComponent>("ArrowComp");
	ArrowComp->SetupAttachment(RootComponent);
	bDoOnce =true;
}

void AAsteroidBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if(ensure(AttributeComp))
	AttributeComp->OnHealthChanged.AddDynamic (this,&AAsteroidBase::OnHealthChanged);
	Mesh->OnComponentHit.AddDynamic(this,&AAsteroidBase::OnHit);
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
	if(IsValid(InstigatorActor))
	{
		return;
	}
	if(NewHealth<=0&&Delta<0.0f)
	{
		Destroy();
	}
}

void AAsteroidBase::OnOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{

}

void AAsteroidBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                          FVector NormalImpulse, const FHitResult& Hit)
{
	if(OtherActor == UGameplayStatics::GetPlayerPawn(GetWorld(),0)&&bDoOnce==true)
	{
		TObjectPtr<UAttributeComponent> ATC = Cast<UAttributeComponent>( UAttributeComponent::GetAttributes(OtherActor));
		
		
		if(ensure(ATC))
		{
			TObjectPtr<ASpaceShip> Player = Cast<ASpaceShip> (ATC->GetOwner());
			FString CombinedString = FString::Printf(TEXT("Collision with asteroid"));
			GEngine->AddOnScreenDebugMessage(-1,0.5f,FColor::Green,CombinedString);
			ATC->ApplyHealthChange(-1);
			bDoOnce =false;
			Player->StartHitStop(NormalImpulse);
			GetWorld()->GetTimerManager().SetTimer(CollisionTimer,FTimerDelegate::CreateLambda(
				[&](){
					UE_LOG(LogTemp,Warning,TEXT("Clear Time"));
			GetWorld()->GetTimerManager().ClearTimer(CollisionTimer);
					bDoOnce = true;
		}), 0.5f,false
			);
		}
	}
}

