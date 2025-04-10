// Fill out your copyright notice in the Description page of Project Settings.

#include "MastermindBoard.h"
#include "MastermindRow.h"
#include "MastermindSphere.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMastermindBoard::AMastermindBoard()
{
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMastermindBoard::BeginPlay()
{
    Super::BeginPlay();

    Manager = Cast<AMasterMindGM>(UGameplayStatics::GetActorOfClass(GetWorld(), AMasterMindGM::StaticClass()));
    if (!Manager)
    {
        UE_LOG(LogTemp, Error, TEXT("Manager not found!"));
        return;
    }

    if (!RowClass)
    {
        UE_LOG(LogTemp, Error, TEXT("RowClass not set! Please assign a Blueprint of AMastermindRow."));
        return;
    }

    // Crée les lignes de jeu
    for (int i = 0; i < RowCount; i++)
    {
        FVector Location = GetActorLocation() + FVector(0, 0, -i * RowSpacing);
        FRotator Rotation = GetActorRotation();
        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;

        AMastermindRow* NewRow = GetWorld()->SpawnActor<AMastermindRow>(RowClass, Location, Rotation, SpawnParams);
        if (NewRow)
        {
            NewRow->Manager = Manager;
            Rows.Add(NewRow);

            // Désactive les interactions sauf pour la première ligne
            for (AActor* SphereActor : NewRow->PlayerSpheres)
            {
                UMastermindSphere* Sphere = SphereActor->FindComponentByClass<UMastermindSphere>();
                if (Sphere)
                {
                    if (i == 0)
                    {
                        Sphere->Unblock();
                    }
                    else
                    {
                        Sphere->Block();
                    }
                }
            }
        }
    }

    Manager->OnSolutionChecked.AddDynamic(this, &AMastermindBoard::HandleSolutionChecked);
}

void AMastermindBoard::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AMastermindBoard::HandleSolutionChecked(int32 Correct, int32 Misplaced)
{
    UE_LOG(LogTemp, Warning, TEXT("Résultat: %d bien placés, %d mal placés"), Correct, Misplaced);
}

void AMastermindBoard::OnRowSubmitted(uint8 GoodPlaces, uint8 WrongPlaces)
{
    UE_LOG(LogTemp, Warning, TEXT("Row Submitted - Good: %d, Wrong: %d"), GoodPlaces, WrongPlaces);

    if (CurrentRowIndex < Rows.Num())
    {
        // Bloque la ligne précédente
        for (AActor* SphereActor : Rows[CurrentRowIndex]->PlayerSpheres)
        {
            UMastermindSphere* Sphere = SphereActor->FindComponentByClass<UMastermindSphere>();
            if (Sphere)
            {
                Sphere->Block();
            }
        }

        CurrentRowIndex++;

        // Débloque la ligne suivante
        if (CurrentRowIndex < Rows.Num())
        {
            for (AActor* SphereActor : Rows[CurrentRowIndex]->PlayerSpheres)
            {
                UMastermindSphere* Sphere = SphereActor->FindComponentByClass<UMastermindSphere>();
                if (Sphere)
                {
                    Sphere->Unblock();
                }
            }
        }
    }
}