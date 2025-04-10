#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MasterMindGM.generated.h"

// Déclaration du delegate BlueprintAssignable avec 2 paramètres : bons emplacements et mauvais emplacements
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSolutionCheckedDelegate, int32, GoodPlaces, int32, WrongPlaces);

UCLASS()
class AIX_GD3_FILROUGE_API AMasterMindGM : public AActor
{
	GENERATED_BODY()

public:
	// Constructeur
	AMasterMindGM();

protected:
	// Fonction appelée au début du jeu
	virtual void BeginPlay() override;

private:
	// Solution secrète (liste de 4 entiers entre 0 et 5)
	UPROPERTY()
	TArray<int32> Solution;

public:
	// Delegate appelé après vérification
	UPROPERTY(BlueprintAssignable)
	FOnSolutionCheckedDelegate OnSolutionChecked;

	// Génère une nouvelle solution aléatoire
	UFUNCTION(BlueprintCallable)
	void GenerateSolution();

	// Vérifie une proposition du joueur
	UFUNCTION(BlueprintCallable)
	void CheckSolution(const TArray<int32>& PlayerProposal);

	// Retourne une couleur à partir d'un numéro (0 à 5)
	UFUNCTION(BlueprintCallable)
	FLinearColor GetColor(int32 ColorIndex) const;

	// Fonction pour ajouter une nouvelle ligne de sphères
	UFUNCTION(BlueprintCallable)
	void AddNewRow();
};