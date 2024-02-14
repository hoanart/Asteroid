// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AsteroidBase.h"
#include "AsteroidBig.generated.h"

/**
 * 
 */
UCLASS()
class ASTEROID_API AAsteroidBig : public AAsteroidBase
{
	GENERATED_BODY()
	AAsteroidBig();

protected:
	virtual void PostInitializeComponents() override;
};
