// Fill out your copyright notice in the Description page of Project Settings.


#include "Barril.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ABarril::ABarril()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> 
		Barril(TEXT("StaticMesh'/Game/Geometry/BarrilMesh/BarrilStaticMesh.BarrilStaticMesh'"));

	//Malla
	BarrilMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Barril_Mesh"));
	BarrilMesh->SetStaticMesh(Barril.Object);
	BarrilMesh->SetRelativeScale3D(FVector(0.4, 0.4, 0.4));
	BarrilMesh->SetRelativeRotation(FRotator(0.0f, 90.f, 0.f));
	SetRootComponent(BarrilMesh);

	//Malla de colision
	BarrilColision = CreateDefaultSubobject<USphereComponent>(TEXT("Barril_Colision"));
	BarrilColision->SetSphereRadius(255.0f);
	BarrilColision->SetRelativeLocation(FVector(0.0f, 0.0f, 200.0f));
	BarrilColision->SetVisibility(true);
	BarrilColision->SetupAttachment(GetRootComponent());



	//Movimiento
	BarrilMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Barril_Movimiento"));
	BarrilMovement->UpdatedComponent = BarrilMesh;
	BarrilMovement->InitialSpeed = 0.0f;
	BarrilMovement->MaxSpeed = 1000.0f;
	BarrilMovement->bRotationFollowsVelocity = false;
	BarrilMovement->bShouldBounce = true;
	BarrilMovement->Bounciness = 0.7f;
	BarrilMovement->Friction = 0.2;

	RotationSpeed = 150.f;


}

// Called when the game starts or when spawned
void ABarril::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABarril::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator currentrotator = GetActorRotation();
	currentrotator.Pitch += RotationSpeed * DeltaTime;

	if (currentrotator.Pitch > 360.0f) {
		currentrotator.Pitch -= 360.0f;
	}

	SetActorRotation(currentrotator);

}

void ABarril::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Entro")));

	SpeedIncrease = 250.f;
	FVector CurrentVelocity = BarrilMovement->Velocity;
	FVector NewVelocity = CurrentVelocity.GetSafeNormal() *
		(CurrentVelocity.Size() + this->SpeedIncrease);

	if (NewVelocity.Size() <= BarrilMovement->MaxSpeed) {
		BarrilMovement->Velocity = NewVelocity;
	}


}

