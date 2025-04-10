#include "MastermindRow.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"

// Sets default values
AMastermindRow::AMastermindRow()
{
	// Enable tick for this actor
	PrimaryActorTick.bCanEverTick = true;
}

void AMastermindRow::BeginPlay()
{
	Super::BeginPlay();
}

void AMastermindRow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Fonction pour ajouter une nouvelle ligne de sphères
void AMastermindRow::AddNewRow()
{
	// Définir la position de spawn
	FVector SpawnLocation = GetActorLocation() + FVector(0, 0, 100);  // Déplacer légèrement vers le haut
	AMastermindRow* NewRow = GetWorld()->SpawnActor<AMastermindRow>(AMastermindRow::StaticClass(), SpawnLocation, FRotator::ZeroRotator);

	// Vérifier si la nouvelle ligne a été créée
	if (NewRow)
	{
		NewRow->Manager = Manager;  // Assigner le Manager
	}
}