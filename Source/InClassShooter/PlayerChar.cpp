// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerChar.h"
#include "PortalComponent.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"



// Sets default values
APlayerChar::APlayerChar()
{
	PrimaryActorTick.bCanEverTick = true;

	cam = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCam"));
	cam->SetupAttachment(GetCapsuleComponent());
	cam->bUsePawnControlRotation = true;

	hingeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HingeWeapon"));
	hingeMesh->SetupAttachment(cam);
	hingeMesh->bCastDynamicShadow = true;
	hingeMesh->CastShadow = false;
	// hingeMesh->SetRelativeLocation(FVector())
	hingeMesh->SetOnlyOwnerSee(true);

	UCharacterMovementComponent* cmove = GetCharacterMovement();
	cmove->BrakingFriction = 10.f;
	cmove->MaxAcceleration = 10000.f;
	cmove->MaxWalkSpeed = 1000.f;
	cmove->JumpZVelocity = 570.f;
	cmove->AirControl = 2.f;
}

// Called when the game starts or when spawned
void APlayerChar::BeginPlay()
{
	Super::BeginPlay();
	UWorld* w = GetWorld();
	lPortal = w->SpawnActor<APortalComponent>(portalBP, FVector(0, 0, -1000), FRotator(0, 0, 0));
	rPortal = w->SpawnActor<APortalComponent>(portalBP, FVector(0, 0, -1000), FRotator(0, 0, 0));
	lPortal->isLeftPortal = true;
	lPortal->Prepare();
	rPortal->Prepare();

}

// Called every frame
void APlayerChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("Shoot", this, &APlayerChar::OnUseItem);
	
	PlayerInputComponent->BindAxis("Forward", this, &APlayerChar::MoveForward);
	PlayerInputComponent->BindAxis("Right", this, &APlayerChar::MoveRight);

	PlayerInputComponent->BindAxis("MouseRight", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("MouseUp", this, &APawn::AddControllerPitchInput);

}

void APlayerChar::MoveForward(float vel) {
	if (vel != 0)
		AddMovementInput(GetActorForwardVector(), vel * moveSpeed);
		//UE_LOG(LogTemp, Warning, TEXT("adelante"));
}

void APlayerChar::MoveRight(float vel) {
	if (vel != 0)
		AddMovementInput(GetActorRightVector(), vel * moveSpeed);
		//UE_LOG(LogTemp, Warning, TEXT("andelao"));
}

void APlayerChar::OnUseItem(float leftClick) {
	if (leftClick == 0) {
		onCooldown = false;
		return;
	}
	if (onCooldown)
		return;

	if (leftClick == 1)
		evOnUseItem.Broadcast(true);
	else
		evOnUseItem.Broadcast(false);

	onCooldown = true;
}
