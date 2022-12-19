// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"

// Sets default values
ABullet::ABullet() {
	PrimaryActorTick.bCanEverTick = true;

	collComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	collComp->InitSphereRadius(20.f);
	RootComponent = collComp;
	collComp->BodyInstance.SetCollisionProfileName("Projectile");
	collComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	collComp->CanCharacterStepUpOn = ECB_No;

	projMove = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjMovement"));
	projMove->UpdatedComponent = collComp;
	projMove->InitialSpeed = 5000.f;
	projMove->MaxSpeed = 5000.f;
	projMove->bRotationFollowsVelocity = true;
	projMove->bShouldBounce = true;

	InitialLifeSpan = 3.f;	
}

// Called when the game starts or when spawned
void ABullet::BeginPlay() {
	Super::BeginPlay();
	collComp->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnHit);
}

void ABullet::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit) {
	if(OtherActor && IsValid(OtherActor)) {
		UE_LOG(LogTemp, Warning, TEXT("Golpié %s"), *(OtherActor->GetName()));
		//AEnemy* e = Cast<Enemy>(hit.getActor());
		// e->Hit(x);
		// Destroy();
	}
}
