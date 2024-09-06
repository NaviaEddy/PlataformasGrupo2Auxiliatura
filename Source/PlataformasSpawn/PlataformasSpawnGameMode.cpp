// Copyright Epic Games, Inc. All Rights Reserved.

#include "PlataformasSpawnGameMode.h"
#include "PlataformasSpawnCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Plataformas.h"
#include "Barril.h"

APlataformasSpawnGameMode::APlataformasSpawnGameMode()
{

	PrimaryActorTick.bCanEverTick = true;

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	Posicion = FVector(1180.f, -370.f, 140.f);
	Rotacion = FRotator(0.f, 0.f, 2.f);
	PosicionAuxiliar = 510.f;
	Time = 0.f;
	spawnsPlataformas = 0;
}

void APlataformasSpawnGameMode::BeginPlay()
{
	Super::BeginPlay();
	for (int i = 0; i < 4; i++) {
		PT = GetWorld()->SpawnActor<APlataformas>(APlataformas::StaticClass(), Posicion, Rotacion);
		ContPlataformas.Add(PT);
		Posicion.Z += 500.0f;
		Posicion.Y += PosicionAuxiliar + FMath::FRandRange(10.f, 25.f);
		Rotacion.Roll *= -1;
		PosicionAuxiliar *= -1;
	}

	//spawnsPlataformas = ContPlataformas.Num() - 1;
	spawnsPlataformas = 0;//4 elementos [0,1,2,3]
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, 
		FString::Printf(TEXT("Cantidad del contenedor: %d"), ContPlataformas.Num()));

	
}

void APlataformasSpawnGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	Time += DeltaTime;

	//Codigo para eliminar plataformas con un reloj.
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue,
		//FString::Printf(TEXT("Cantidad del contenedor: %d"), ContPlataformas.Num()));

	if (Time > 3.0f) {
		if (spawnsPlataformas != 3) {
			Ba = GetWorld()->SpawnActor<ABarril>(ABarril::StaticClass(), FVector(1210.f, 970.f, 1900.f), FRotator::ZeroRotator);
			AActor* plataforma = ContPlataformas[spawnsPlataformas];
			plataforma->Destroy();
			ContPlataformas.RemoveAt(ContPlataformas.Num() - 1);
			Time = 0.f;
			spawnsPlataformas += 1;
		}
		

	}
	
}
