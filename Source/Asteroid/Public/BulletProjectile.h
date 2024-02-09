// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectileBase.h"
#include "BulletProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ASTEROID_API ABulletProjectile : public AProjectileBase
{
	GENERATED_BODY()
public:
	ABulletProjectile();

protected:
	virtual void PostInitializeComponents() override;
protected:
	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	
	
};
