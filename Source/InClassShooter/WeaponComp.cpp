// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComp.h"
#include "PortalWall.h"
#include "Bullet.h"
#include "PortalComponent.h"
#include "EngineUtils.h"
#include "PlayerChar.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UWeaponComp::UWeaponComp() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	

	// ...
}


// Called when the game starts
void UWeaponComp::BeginPlay() {
	Super::BeginPlay();

	// ...

}


// Called every frame
void UWeaponComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UWeaponComp::AttachToPlayer(APlayerChar* target) {

	selfActor = target;
	if (selfActor) {
		player = target;
		FAttachmentTransformRules rules(EAttachmentRule::SnapToTarget, true);
		GetOwner()->AttachToComponent(selfActor->GetWeaponPoint(), rules, TEXT("WeaponPoint"));

		selfActor->evOnUseItem.AddDynamic(this, &UWeaponComp::Fire);
	}


}


/*FVector relPosition = HitPos +
FVector(
	relPositionOnWall.X,
	FMath::Min(
		FMath::Max(HitPos.Y / 2, relPositionOnWall.Y),
		(Hit->GetActor()->GetActorScale3D().Y * 2) - (HitPos.Y / 2)
	),
	FMath::Min(
		FMath::Max(HitPos.Z / 2, relPositionOnWall.Z),
		(Hit->GetActor()->GetActorScale3D().Z * 2) - (HitPos.Z / 2)
	)
);*/

FVector UWeaponComp::TryAddPortal(FHitResult* Hit)
{
	FVector HitPos = FVector(Hit->TraceEnd - Hit->TraceStart) + Hit->ImpactPoint;
	FVector RelativePortalOrigin = UKismetMathLibrary::InverseTransformDirection(Hit->GetActor()->GetActorTransform(), HitPos);
	FVector PosicionFinalPortal(Hit->ImpactPoint.X, 
								ConstraintToWallY(HitPos.Y, Hit),
								ConstraintToWallZ(HitPos.Z, Hit));

	return PosicionFinalPortal;
}

float UWeaponComp::ConstraintToWallY(float PortalY, FHitResult* Hit) {
	APortalWall* pared = Cast<APortalWall>(Hit->GetActor());
	if (pared) {
		float clampedY = ClampPointToWall(PortalY, pared->getWallSize().Y, 180 / 2);
		return clampedY;
	}
	return NULL;
	
}

float UWeaponComp::ConstraintToWallZ(float PortalZ, FHitResult* Hit) {

	APortalWall* pared = Cast<APortalWall>(Hit->GetActor());
	if (pared) {
		float clampedZ = ClampPointToWall(PortalZ, pared->getWallSize().Z, 249 / 2);
		return clampedZ;
	}
	return NULL;
}

float UWeaponComp::ClampPointToWall(float Point, float WallSize, float PortalRadius) {

	float offset = FMath::Clamp(WallSize / 2 - PortalRadius - abs(Point), -1000000000000000000.0f,0);
	
	bool PointBool = Point < 0;

	if (PointBool) {
		offset *= 1;
	}
	else {
		offset *= -1;
	}

	return Point - offset;

}

void UWeaponComp::Fire(bool leftClick) {
	if (!selfActor || !selfActor->GetController())
		return;
	UE_LOG(LogTemp, Warning, TEXT("pium"));

	UWorld* const w = GetWorld();
	UCameraComponent* cam = selfActor->GetCam();
	FVector const vStart = cam->GetComponentLocation();
	FVector const vEnd = vStart + UKismetMathLibrary::GetForwardVector(cam->GetComponentRotation()) * 50000;
	FVector finalPortalPosition;
	//APortalComponent *PortalSpawned;
	FCollisionQueryParams inParams;
	inParams.AddIgnoredActor(selfActor);

	FCollisionResponseParams outParams;

	FHitResult hit;

	if (leftClick) {
		w->LineTraceSingleByChannel(hit, vStart, vEnd, ECC_Camera, inParams, outParams);
		DrawDebugLine(w, vStart, vEnd, hit.bBlockingHit ? FColor::Red : FColor::Blue, false,
			5.f, 0, 10.f);
		UE_LOG(LogTemp, Warning, TEXT("LeftPortal"))
	}
	else {
		w->LineTraceSingleByChannel(hit, vStart, vEnd, ECC_Camera, inParams, outParams);
		DrawDebugLine(w, vStart, vEnd, hit.bBlockingHit ? FColor::Green : FColor::Yellow, false,
			5.f, 0, 10.f);
		UE_LOG(LogTemp, Warning, TEXT("RightPortal"))
	}
	UE_LOG(LogTemp, Warning, TEXT("Trace %s to %s"), *vStart.ToCompactString(), *vEnd.ToCompactString());

	if (hit.bBlockingHit && IsValid(hit.GetActor())) {
		APortalWall* hitActor = Cast<APortalWall>(hit.GetActor());
		if (hitActor)//Comprobamos que el actor golpeado sea el de un muro de portal
			finalPortalPosition = TryAddPortal(&hit); //Obtenemos la posicion definitiva del nuevo portal
		if (player) {
			if (leftClick) {
				player->lPortal->SetActorLocation(finalPortalPosition);
				player->lPortal->SetActorRotation(hit.ImpactNormal.Rotation() + FRotator(-90, 0, 0) + hit.GetActor()->GetActorRotation());
			}
			else {
				player->rPortal->SetActorLocation(finalPortalPosition);
				player->rPortal->SetActorRotation(hit.ImpactNormal.Rotation() + FRotator(-90, 0, 0) + hit.GetActor()->GetActorRotation());
			}
		}
			
			//PortalSpawned = w->SpawnActor<APortalComponent>(portalBP,finalPortalPosition, hit.ImpactNormal.Rotation() + FRotator(-90,0,0) + hit.GetActor()->GetActorRotation());
			//PortalSpawned->isLeftPortal = leftClick;
			//PortalSpawned->Prepare();

		UE_LOG(LogTemp, Warning, TEXT("Golpié %s"), *(hit.GetActor()->GetName()));
		//Aqui comprobar que el objeto golpeado es un muro apto para portales
		//Si es asi crear el portal correpondiente al disparo realizado
		//AEnemy* e = Cast<Enemy>(hit.getActor());
		// e->Hit(x);

	} else {
		UE_LOG(LogTemp, Warning, TEXT("No >:("));
	}



}
