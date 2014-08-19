//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//

#include <fstream>

#include "NSRunAction.hh"
#include "NSAnalysis.hh"
#include "NSPrimaryGeneratorAction.hh"
#include "NSDetectorConstruction.hh"
#include "NSRun.hh"

#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include "G4Material.hh"
#include "G4String.hh"

NSRunAction::NSRunAction()
: G4UserRunAction()
{
  // Create analysis manager
  // The choice of analysis technology is done via selection of a namespace
  // in NSAnalysis.hh
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  G4cout << "Using " << analysisManager->GetType() << G4endl;

  // Create directories if using UI commands
  //analysisManager->SetHistoDirectoryName("histograms");
  //analysisManager->SetNtupleDirectoryName("ntuple");

  // Default Settings
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetFirstHistoId(1);
  analysisManager->SetFileName("singleRun");

  // Book histograms, ntuple
  
  // Creating histograms
  analysisManager->CreateH1("h1","Entered inner", 2, -0.5, 1.5);
  analysisManager->CreateH1("h2","Energy Deposited", 1000, 0, 30*MeV);

  // Creating ntuple
  analysisManager->CreateNtuple("singleRun", "Event info from one run");
  analysisManager->CreateNtupleIColumn("EntInner");
  analysisManager->CreateNtupleDColumn("Edep");
  analysisManager->CreateNtupleDColumn("primx");
  analysisManager->CreateNtupleDColumn("primy");
  analysisManager->CreateNtupleDColumn("primz");
  analysisManager->CreateNtupleDColumn("primdx");
  analysisManager->CreateNtupleDColumn("primdy");
  analysisManager->CreateNtupleDColumn("primdz");
  analysisManager->FinishNtuple();

}

NSRunAction::~NSRunAction()
{
  delete G4AnalysisManager::Instance();
}

G4Run* NSRunAction::GenerateRun()
{
  return new NSRun; 
}

void NSRunAction::BeginOfRunAction(const G4Run*)
{
  // Inform the runManager to save random number seed
  // G4RunManager::GetRunManager()->SetRandomNumberStore(false);

  // Get analysis manager
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  // Open an output file for histograms
  analysisManager->OpenFile();
}

void NSRunAction::EndOfRunAction(const G4Run* run)
{

  // Print histogram statistics
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  G4double meanPer  = analysisManager->GetH1(1)->mean();
  G4double meanEdep = analysisManager->GetH1(2)->mean();

  if ( analysisManager->GetH1(1) ) {
    G4cout << "\n ----> print histograms statistic ";
    if(isMaster) {
      G4cout << "for the entire run \n" << G4endl; 
    }
    else {
      G4cout << "for the local thread \n" << G4endl; 
    }
    
    G4cout << " Edep : mean = " 
       << G4BestUnit(analysisManager->GetH1(2)->mean(), "Energy") 
       << " rms = " 
       << G4BestUnit(analysisManager->GetH1(2)->rms(),  "Energy") << G4endl;

    G4cout << " Primary particles entering detector = " 
       << analysisManager->GetH1(1)->mean() << G4endl;
  }

  // Save histograms & ntuple
  analysisManager->Write();
  analysisManager->CloseFile();

  // Get primary particle energy
  G4double particleEnergy = 0.;
  const NSPrimaryGeneratorAction* generatorAction
    = static_cast<const NSPrimaryGeneratorAction*>
      (G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction());
  if (generatorAction)
  {
    const G4ParticleGun* particleGun = generatorAction->GetParticleGun();
    particleEnergy = particleGun->GetParticleEnergy();
  }

  // Get detector parameters
  const NSDetectorConstruction* detectorConstruction
    = static_cast<const NSDetectorConstruction*>
    (G4RunManager::GetRunManager()->GetUserDetectorConstruction());

  G4double shield1_sizeXY = detectorConstruction->GetShield1SizeXY();
  G4double shield2Ratio = detectorConstruction->GetShield2Ratio();
  G4double detRatio = detectorConstruction->GetDetRatio();
  G4String world_mat = detectorConstruction->GetWorldMaterial()->GetName();
  G4String shield1_mat = detectorConstruction->GetShield1Material()->GetName();
  G4String shield2_mat = detectorConstruction->GetShield2Material()->GetName();
  G4String det_mat = detectorConstruction->GetDetMaterial()->GetName();

  // Find which shield layer uses BdP (if any) and get dopant percent
  G4String mat[] = {world_mat, shield1_mat, shield2_mat, det_mat};
  G4int nOfLayers = 4;
  G4int i;
  G4Material* mat_i;
  const G4double* fracVec;
  G4double percentBdP = 0;

  for (i = 0; i < nOfLayers; i++)
  {
    if (mat[i].G4String::contains("BdP"))
    {
      mat_i = G4Material::GetMaterial(mat[i]);
      fracVec = mat_i->GetFractionVector();
      percentBdP = fracVec[0];
    }
  }

  // Get run id
  G4int runID = run->GetRunID();

  // Output text file with run information
  // Can be put into tree with "TreeMac.C"

  // Open file for writing
  G4String outfileName = "NS.out";
  std::ofstream outfile;
  if (runID == 0) // New set of runs
  {
    outfile.open(outfileName, std::ofstream::out | std::ofstream::trunc);
  }
  // Open file for appending
  else // Continuing set of runs
  {
    outfile.open(outfileName, std::ofstream::out | std::ofstream::app);
  }
  
  if (outfile.is_open())
    {
      outfile << runID << "\t" << particleEnergy/MeV << "\t" << shield1_sizeXY/m
              << "\t" << shield2Ratio << "\t" << detRatio << "\t" << percentBdP
              << "\t" << mat[0] << "\t" << mat[1] << "\t" << mat[2]
              << "\t" << mat[3] << "\t" << meanEdep/MeV << "\t" << meanPer
              << G4endl;
    }
  else
    {
      G4cout << "File " << outfile << " does not exist!" << G4endl;
    }

    outfile.close();
  }
}
