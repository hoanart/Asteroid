// Fill out your copyright notice in the Description page of Project Settings.


#include "AsteroidBase.h"

#include "AttributeComponent.h"
#include "SpaceShip.h"
#include "Asteroid/AsteroidGameModeBase.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/MovementComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
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
	SpawnTheta = 30.0f;
	bDoOnce =true;
	
}

void AAsteroidBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SetLifeSpan(20.f);
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

void AAsteroidBase::CreateSubAsteroid()
{
	if(IsValid(SubAsteroidClass))
	{
		FVector Loc = GetActorLocation();
		FRotator Rot1 = FRotator(0.f,GetActorRotation().Yaw+SpawnTheta,0.f);
		FRotator Rot2 = FRotator(0.f,GetActorRotation().Yaw-SpawnTheta,0.f);
		
		UE_LOG(LogTemp,Display,TEXT("%s"),*Rot1.ToString());
		
			GetWorld()->SpawnActor<AActor>(SubAsteroidClass,Loc,Rot1);		
			GetWorld()->SpawnActor<AActor>(SubAsteroidClass,Loc,Rot2);				
	}

}

void AAsteroidBase::CollisionTimerElapsed()
{
		GetWorld()->GetTimerManager().ClearTimer(CollisionTimer);
	bDoOnce = true;
}


void AAsteroidBase::OnHealthChanged(AActor* InstigatorActor, UAttributeComponent* OwningComp, float NewHealth, float Delta)
{

	if(NewHealth<=0&&Delta<0.0f)
	{
		UE_LOG(LogTemp,Display,TEXT("Destroy"));
		UGameplayStatics::PlaySound2D(GetWorld(),ExplosionSound);
		Destroy();
		CreateSubAsteroid();
		TObjectPtr<AAsteroidGameModeBase> GameMode = Cast<AAsteroidGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
		if(ensure(GameMode))
		{
			GameMode->bDestroyAsteroid = true;
		}
		GameMode->AddToTotalScore(AttributeComp->GetScore());
		
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
			GetWorld()->GetTimerManager().SetTimer(CollisionTimer,this,&AAsteroidBase::CollisionTimerElapsed, 0.5f,false
			);
		}
	}
}
