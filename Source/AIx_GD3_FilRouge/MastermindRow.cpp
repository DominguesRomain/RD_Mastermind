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

// Fonction pour ajouter une nouvelle ligne de sph�res
void AMastermindRow::AddNewRow()
{
	// D�finir la position de spawn
	FVector SpawnLocation = GetActorLocation() + FVector(0, 0, 100);  // D�placer l�g�rement vers le haut
	AMastermindRow* NewRow = GetWorld()->SpawnActor<AMastermindRow>(AMastermindRow::StaticClass(), SpawnLocation, FRotator::ZeroRotator);

	// V�rifier si la nouvelle ligne a �t� cr��e
	if (NewRow)
	{
		NewRow->Manager = Manager;  // Assigner le Manager
	}
}