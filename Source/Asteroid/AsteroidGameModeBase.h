// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AsteroidGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class ASTEROID_API AAsteroidGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	AAsteroidGameModeBase();

	virtual void StartPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly,Category = "AI")
	TArray<TSubclassOf<AActor>> AsteroidClasses;
	UPROPERTY(EditDefaultsOnly,Category = "AI")
	TObjectPtr<class UEnvQuery> SpawnPawnQuery;
	
	UPROPERTY(EditDefaultsOnly,Category = "AI")
	TObjectPtr<class UCurveFloat> DifficultyCurve;

	UPROPERTY(EditDefaultsOnly,Category = "AI")
	float SpawnTimerInterval;

protected:
	FTimerHandle SpawnBotsTimer;
};
