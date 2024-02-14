// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletProjectile.h"

#include "Components/BoxComponent.h"

ABulletProjectile::ABulletProjectile()
{
}

void ABulletProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	BoxComp->OnComponentBeginOverlap.AddDynamic(this,&ABulletProjectile::OnOverlap);
	
}

void ABulletProjectile::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	
}
