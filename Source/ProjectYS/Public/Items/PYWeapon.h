// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/PYItem.h"
#include "PYWeapon.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTYS_API APYWeapon : public APYItem
{
	GENERATED_BODY()

	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
	
};
