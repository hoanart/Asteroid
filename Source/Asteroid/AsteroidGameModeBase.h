// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "GameFramework/GameModeBase.h"
#include "AsteroidGameModeBase.generated.h"


/**
 * 
 */
//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFinishedGame);
UCLASS()
class ASTEROID_API AAsteroidGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	AAsteroidGameModeBase();

	virtual void StartPlay() override;
	
public:
	void AddToTotalScore(const int& Score);
	UFUNCTION(BlueprintImplementableEvent)
	void FinishGame();
protected:

	UFUNCTION()
	void SpawnBotTimerElapsed();

	UFUNCTION(BlueprintNativeEvent)
	void CountDownTimerElapsed();
	UFUNCTION()
	void OnQueryCompleted(class UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = "Timer")
	bool bDestroyAsteroid;

protected:
	UPROPERTY(EditDefaultsOnly,Category = "AI")
	TArray<TSubclassOf<class AAsteroidBase>> AsteroidClasses;
	UPROPERTY(EditDefaultsOnly,Category = "AI")
	TObjectPtr<class UEnvQuery> SpawnPawnQuery;
	
	UPROPERTY(EditDefaultsOnly,Category = "AI")
	TObjectPtr<class UCurveFloat> DifficultyCurve;
	
	UPROPERTY(EditDefaultsOnly,Category = "AI")
	float SpawnTimerInterval;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category = "Timer")
	float Count;
	// UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category = "Timer")
	// float MaxAsteroidCount;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category = "Score")
	int32 TotalScore;
protected:
	FTimerHandle SpawnBotsTimer;
	FTimerHandle CountDownTimer;
};
