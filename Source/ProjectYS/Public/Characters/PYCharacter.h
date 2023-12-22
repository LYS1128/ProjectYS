// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PYCharacter.generated.h"

UCLASS()
class PROJECTYS_API APYCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APYCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void SetWidget(class UPYUserWidget* InStudyUserWidget) {}

public:
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	class UPYStatComponent* GetStatComponent() { return StatComponent; }

public:
	UFUNCTION()
	virtual void CheckHit();

	UFUNCTION()
	virtual void OnCharacterDeath();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ASPlayerCharacter, Meta = (AllowPrivateAccess))
	TObjectPtr<class UPYStatComponent> StatComponent;

protected:
	float AttackRange = 200.f;

	float AttackRadius = 50.f;

};
