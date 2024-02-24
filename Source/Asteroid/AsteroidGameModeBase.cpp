// Copyright Epic Games, Inc. All Rights Reserved.


#include "AsteroidGameModeBase.h"

#include "AsteroidBase.h"
#include "AttributeComponent.h"
#include "EngineUtils.h"
#include "SpaceShip.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "Kismet/GameplayStatics.h"

AAsteroidGameModeBase::AAsteroidGameModeBase()
{
	SpawnTimerInterval = 2.0f;
	Count = 0.01f;
}

void AAsteroidGameModeBase::StartPlay()
{
	Super::StartPlay();
	GetWorldTimerManager().SetTimer(SpawnBotsTimer,this,&AAsteroidGameModeBase::SpawnBotTimerElapsed,SpawnTimerInterval,true);
	GetWorldTimerManager().SetTimer(CountDownTimer,this,&AAsteroidGameModeBase::CountDownTimerElapsed,1.f,true);
}

void AAsteroidGameModeBase::SpawnBotTimerElapsed()
{
	int32 NumOfAliveAsteroids = 0;
	for(TActorIterator<AAsteroidBase> It(GetWorld());It;++It )
	{
		TObjectPtr<AAsteroidBase> Asteroid = *It;
		TObjectPtr<UAttributeComponent> AttributeComp = Cast<UAttributeComponent>( Asteroid->GetComponentByClass(UAttributeComponent::StaticClass()));
		if(ensure(AttributeComp)&&AttributeComp->IsAlive())
		{
			NumOfAliveAsteroids++;
		}
	}

	float MaxAsteroidCount = 20.0f;
	if(DifficultyCurve)
	{
		MaxAsteroidCount = DifficultyCurve->GetFloatValue(GetWorld()->TimeSeconds);
	}

	if(NumOfAliveAsteroids>=MaxAsteroidCount)
	{
		return;
	}
	
	TObjectPtr<UEnvQueryInstanceBlueprintWrapper> QueryInstance = UEnvQueryManager::RunEQSQuery(this,SpawnPawnQuery,this,EEnvQueryRunMode::RandomBest5Pct,nullptr);
	if(ensure(QueryInstance))
	{
		QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this,&AAsteroidGameModeBase::OnQueryCompleted);
	}
}

void AAsteroidGameModeBase::CountDownTimerElapsed_Implementation()
{
	
}

void AAsteroidGameModeBase::OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance,
                                             EEnvQueryStatus::Type QueryStatus)
{
	if(QueryStatus!=EEnvQueryStatus::Success)
	{
		UE_LOG(LogTemp,Warning,TEXT("Spawn asteroid Eqs Query Failed!"));
		return ;
	}
	TObjectPtr<ASpaceShip> Player =  Cast<ASpaceShip>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
	if(!ensure(Player))
	{
		UE_LOG(LogTemp,Warning,TEXT("Need Spaceship class Player"));
	}

	FVector PlayerLoc = Player->GetActorLocation();
	
	TArray<FVector> Location = QueryInstance->GetResultsAsLocations();

	if(Location.IsValidIndex(0))
	{
		uint32 rIdx = FMath::RandRange(0,AsteroidClasses.Num()-1);
		FVector ActorLoc = FVector(Location[0].X,Location[0].Y,980.f);
		FVector Dir =  PlayerLoc - ActorLoc;
		FRotator ActorRot = FRotationMatrix::MakeFromX(Dir).Rotator();
		GetWorld()->SpawnActor<AActor>(AsteroidClasses[rIdx],ActorLoc,FRotator(0.f,ActorRot.Yaw,0.f));
	}
}

