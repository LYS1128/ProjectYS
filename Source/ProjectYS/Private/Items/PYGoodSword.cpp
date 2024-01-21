// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/PYGoodSword.h"
#include "Characters/PYPlayer.h"
#include "Games/PYPlayerState.h"

void APYGoodSword::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	APYPlayer* Player = Cast<APYPlayer>(OtherActor);
	if (Player)
	{
		APYPlayerState* PS = Cast<APYPlayerState>(Player->GetPlayerState());
		if (true == ::IsValid(PS))
		{
			PS->SetPlayerMode(PlayerMode::MODE_SWORD);

			APYWeapon* CurSword = PS->GetPlayerSword();
			if (true == ::IsValid(CurSword))
			{
				CurSword->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
				//CurSword->Destroy();
			}

			APYWeapon* CurGun = PS->GetPlayerGun();
			if (true == ::IsValid(CurGun))
			{
				//CurGun->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
				CurGun->SetVisible(false);
			}

			PS->SetPlayerSword(this);
		}

		

		FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
		ItemMesh->AttachToComponent(Player->GetMesh(), TransformRules, FName("handsocket_r"));

		
	}
}
