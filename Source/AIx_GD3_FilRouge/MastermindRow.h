#pragma once

#include "CoreMinimal.h"
#include "MasterMindGM.h"
#include "GameFramework/Actor.h"
#include "MastermindRow.generated.h"

UCLASS()
class AIX_GD3_FILROUGE_API AMastermindRow : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMastermindRow();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AMasterMindGM* Manager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UStaticMeshComponent*> AnswerSpheres;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> PlayerSpheres;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Fonction pour ajouter une nouvelle ligne
	UFUNCTION(BlueprintCallable)
	void AddNewRow();

	// Références vers les composants qui représentent les sphères dans le BP
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Spheres")
	UStaticMeshComponent* Sphere1;
    
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Spheres")
	UStaticMeshComponent* Sphere2;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Spheres")
	UStaticMeshComponent* Sphere3;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Spheres")
	UStaticMeshComponent* Sphere4;
};