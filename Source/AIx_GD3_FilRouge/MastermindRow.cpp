#include "MastermindRow.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"

// Sets default values
AMastermindRow::AMastermindRow()
{
	// Enable tick for this actor
	PrimaryActorTick.bCanEverTick = true;
	
	Sphere1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere1"));
	Sphere2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere2"));
	Sphere3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere3"));
	Sphere4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere4"));

	// Attachement des sphères à l'acteur (à la racine ou un autre composant, selon ton besoin)
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	Sphere1->SetupAttachment(RootComponent);
	Sphere2->SetupAttachment(RootComponent);
	Sphere3->SetupAttachment(RootComponent);
	Sphere4->SetupAttachment(RootComponent);

	Sphere1->SetRelativeLocation(FVector(-21.f, -23.f, 49.f)); // Position relative à l'acteur
	Sphere2->SetRelativeLocation(FVector(-21.f, 22.f, 49.f)); // Déplace la deuxième sphère de 100 unités sur l'axe X
	Sphere3->SetRelativeLocation(FVector(24.f, -23.f, 49.f)); // Déplace la troisième sphère de 200 unités sur l'axe X
	Sphere4->SetRelativeLocation(FVector(24.f, 22.f, 49.f)); // Déplace la quatrième sphère de 300 unités sur l'axe X

	Sphere1->SetRelativeScale3D(FVector(0.11f, 0.11f, 0.11f)); // Position relative à l'acteur
	Sphere2->SetRelativeScale3D(FVector(0.11f, 0.11f, 0.11f)); // Position relative à l'acteur
	Sphere3->SetRelativeScale3D(FVector(0.11f, 0.11f, 0.11f)); // Position relative à l'acteur
	Sphere4->SetRelativeScale3D(FVector(0.11f, 0.11f, 0.11f)); // Position relative à l'acteur
}

void AMastermindRow::BeginPlay()
{
	Super::BeginPlay();

	// Ajouter les composants au tableau AnswerSpheres
	AnswerSpheres.Add(Sphere1);
	AnswerSpheres.Add(Sphere2);
	AnswerSpheres.Add(Sphere3);
	AnswerSpheres.Add(Sphere4);

	// Optionnel : afficher les composants dans le log pour tester
	for (auto Sphere : AnswerSpheres)
	{
		if (Sphere)
		{
			UE_LOG(LogTemp, Warning, TEXT("Sphere name: %s"), *Sphere->GetName());
		}
	}
}

void AMastermindRow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Fonction pour ajouter une nouvelle ligne de sph�res
void AMastermindRow::AddNewRow()
{
	// D�finir la position de spawn
	FVector SpawnLocation = GetActorLocation() + FVector(120, 0, 0);
	AMastermindRow* NewRow = GetWorld()->SpawnActor<AMastermindRow>(AMastermindRow::StaticClass(), SpawnLocation, FRotator::ZeroRotator);

	// V�rifier si la nouvelle ligne a �t� cr��e
	if (NewRow)
	{
		NewRow->Manager = Manager;  // Assigner le Manager
	}
}