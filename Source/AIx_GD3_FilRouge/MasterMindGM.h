#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MasterMindGM.generated.h"

// D�claration du delegate BlueprintAssignable avec 2 param�tres : bons emplacements et mauvais emplacements
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSolutionCheckedDelegate, int32, GoodPlaces, int32, WrongPlaces);

UCLASS()
class AIX_GD3_FILROUGE_API AMasterMindGM : public AActor
{
	GENERATED_BODY()

public:
	// Constructeur
	AMasterMindGM();

protected:
	// Fonction appel�e au d�but du jeu
	virtual void BeginPlay() override;

private:
	// Solution secr�te (liste de 4 entiers entre 0 et 5)
	UPROPERTY()
	TArray<int32> Solution;

public:
	// Delegate appel� apr�s v�rification
	UPROPERTY(BlueprintAssignable)
	FOnSolutionCheckedDelegate OnSolutionChecked;

	// G�n�re une nouvelle solution al�atoire
	UFUNCTION(BlueprintCallable)
	void GenerateSolution();

	// V�rifie une proposition du joueur
	UFUNCTION(BlueprintCallable)
	void CheckSolution(const TArray<int32>& PlayerProposal);
	
	// Retourne une couleur � partir d'un num�ro (0 � 5)
	UFUNCTION(BlueprintCallable)
	FLinearColor GetColor(int32 ColorIndex) const;

	// Fonction pour ajouter une nouvelle ligne de sph�res
	UFUNCTION(BlueprintCallable)
	void AddNewRow();
};