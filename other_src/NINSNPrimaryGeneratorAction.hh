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

#ifndef NINSNPrimaryGeneratorAction_h
#define NINSNPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;
class NINSNDetectorConstruction;
class NINSNPrimaryGeneratorMessenger;

class NINSNPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    NINSNPrimaryGeneratorAction(NINSNDetectorConstruction*);
    virtual ~NINSNPrimaryGeneratorAction();

    // method from the base class
    void GeneratePrimaries(G4Event*);         
  
    // method to access particle gun
    const G4ParticleGun* GetParticleGun() const { return fParticleGun; };
  
  private:
    G4ParticleGun*  fParticleGun;            // Pointer to particle gun
    NINSNDetectorConstruction* Detector;        // Pointer to detector construction
    G4int genInShield;                       // Where to generate particles
    G4int genEvaporation;                    // Use evaporation spectrum or not
    NINSNPrimaryGeneratorMessenger* fMessenger; // Pointer to messenger

  public:
    void SetGenInShield (G4int);             // Choose where to generate particles

    void SetGenEvaporation (G4int);             // Choose evaporation spectrum

    G4double GetEvaporationEnergy(void);   // Select a random energy from evaporation spectrum

};

#endif

