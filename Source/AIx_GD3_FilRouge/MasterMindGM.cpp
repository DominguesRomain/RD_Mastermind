#include "MasterMindGM.h"
#include "MastermindRow.h"
#include "Engine/World.h"
#include "MastermindSphere.h" 

// Constructeur
AMasterMindGM::AMasterMindGM()
{
	// Initialise la solution
	GenerateSolution();
}

// Appel� au d�but du jeu
void AMasterMindGM::BeginPlay()
{
	Super::BeginPlay();
}

// G�n�re une nouvelle solution al�atoire
void AMasterMindGM::GenerateSolution()
{
	Solution.Empty();
	for (int32 i = 0; i < 4; ++i)
	{
		Solution.Add(FMath::RandRange(0, 5)); // Valeurs entre 0 et 5
	}
}

// V�rifie une proposition du joueur
void AMasterMindGM::CheckSolution(const TArray<int32>& PlayerProposal)
{
	int32 GoodPlaces = 0;
	int32 WrongPlaces = 0;

	// Comparer les couleurs de la proposition du joueur avec la solution
	for (int32 i = 0; i < Solution.Num(); ++i)
	{
		if (Solution[i] == PlayerProposal[i])
		{
			GoodPlaces++;  // Bon emplacement
		}
		else if (Solution.Contains(PlayerProposal[i]))
		{
			WrongPlaces++;  // Bonne couleur, mauvais emplacement
		}
	}

	// D�clenchement du delegate pour notifier de la v�rification
	OnSolutionChecked.Broadcast(GoodPlaces, WrongPlaces);

	// Ajouter une nouvelle ligne si la proposition est incorrecte
	if (GoodPlaces != 4)  // Supposons que la solution a 4 �l�ments
	{
		AddNewRow();
	}
}

// Retourne une couleur � partir d'un num�ro (0 � 5)
FLinearColor AMasterMindGM::GetColor(int32 ColorIndex) const
{
	switch (ColorIndex)
	{
	case 0: return FLinearColor::Red;
	case 1: return FLinearColor::Green;
	case 2: return FLinearColor::Blue;
	case 3: return FLinearColor::Yellow;
	case 4: return FLinearColor(1.0f, 0.0f, 1.0f); // Magenta
	case 5: return FLinearColor(0.0f, 1.0f, 1.0f); // Cyan
	default: return FLinearColor::Black;
	}
}

// Fonction pour ajouter une nouvelle ligne de sph�res
void AMasterMindGM::AddNewRow()
{
	// Spawning d'une nouvelle ligne de sph�res
	FVector SpawnLocation = FVector(120, 0, 0); 
	AMastermindRow* NewRow = GetWorld()->SpawnActor<AMastermindRow>(AMastermindRow::StaticClass(), SpawnLocation, FRotator::ZeroRotator);

	// Lier le Manager � la nouvelle ligne
	if (NewRow)
	{
		NewRow->Manager = this;
	}
}
