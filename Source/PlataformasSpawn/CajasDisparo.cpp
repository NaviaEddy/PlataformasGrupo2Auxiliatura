// Fill out your copyright notice in the Description page of Project Settings.
#include "CajasDisparo.h"
#include "Projectile.h"

// Sets default values
ACajasDisparo::ACajasDisparo()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Caja(TEXT("StaticMesh'/Game/Geometry/CajaMesh/CilindroMesh.CilindroMesh'"));
	CajaMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh_Caja"));
	CajaMesh->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.25f));
	CajaMesh->SetRelativeRotation(FRotator(0.f, 0.f, 90.f));
	CajaMesh->SetStaticMesh(Caja.Object);
	SetRootComponent(CajaMesh);

	Fire = FVector(0.f, 90.f, 0.f);
	FireRate = 0.5f;
	bCanFire = true;

}

// Called when the game starts or when spawned
void ACajasDisparo::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACajasDisparo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FireShot();
}

void ACajasDisparo::FireShot()
{
	if (bCanFire == true) {
		FVector DirectionRight = FVector(0.f, -1.f, 0.f);
		FVector DirectionLeft = FVector(0.f, 1.f, 0.f);
		const FRotator FireRotationRight = DirectionRight.Rotation();
		const FRotator FireRotationLeft = DirectionLeft.Rotation();
		const FVector SpawnLocationRight = GetActorLocation() + FireRotationRight.RotateVector(Fire);
		const FVector SpawnLocationLeft = GetActorLocation() + FireRotationLeft.RotateVector(Fire);
		UWorld* const World1 = GetWorld();
		if (World1 != nullptr) {
			//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, FString::Printf(TEXT("Spawneo")));
			World1->SpawnActor<AProjectile>(SpawnLocationRight, FireRotationRight);
			World1->SpawnActor<AProjectile>(SpawnLocationLeft, FireRotationLeft);
		}
		bCanFire = false;
		World1->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &ACajasDisparo::ShotTimer, FireRate);
	}
}


void ACajasDisparo::ShotTimer()
{
	bCanFire = true;
}


