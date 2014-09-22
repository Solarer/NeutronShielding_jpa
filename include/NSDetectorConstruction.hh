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


#ifndef NSDetectorConstruction_H
#define NSDetectorConstruction_H 1

#include "G4VUserDetectorConstruction.hh"
#include "G4ThreeVector.hh"
#include "globals.hh"
#include "G4RotationMatrix.hh"
#include "G4Cons.hh"

class G4Material;
class G4Element;
class G4Box;
class G4LogicalVolume;
class G4VPhysicalVolume;
class NSDetectorMessenger;
class NSSD;

class NSDetectorConstruction : public G4VUserDetectorConstruction
{
  private:

    // Materials
    G4Material* worldMat;
    G4Material* shieldMat;
    G4Material* detMat;
    G4Material* scinMat;

	
		// World size
    G4double worldSizeXY, worldSizeZ;

		// Shield size
		G4double shieldSizeXY, shieldSizeZ;

		// Lead size
    G4double detSizeXY, detSizeZ;

		// Scintillator Size
		G4double  scinRadIn1, scinRadIn2, scinRadOut1, scinRadOut2, scinHeight;

		// Volumes
    G4Box*             solidWorld;
    G4LogicalVolume*   logicWorld;
    G4VPhysicalVolume* physWorld;

    G4Box*             		solidShield;
    G4LogicalVolume*   		logicShield;
    G4VPhysicalVolume*  	physShield; 

    G4Box*             solidDet;
    G4LogicalVolume*   logicDet;
    G4VPhysicalVolume* physDet;

    G4Cons*            solidScin;
    G4LogicalVolume*   logicScin;
    G4VPhysicalVolume* physScin;

    NSDetectorMessenger* fMessenger;  // Pointer to messenger
    NSSD* cennsSD;                    // Pointer to sensitive detector


    // Methods
    void DefineMaterials();
    void ComputeParameters();
		void CalcSlopes(G4double*, G4double*, G4int);
    G4VPhysicalVolume* ConstructDetector();

  public:

    NSDetectorConstruction();
   ~NSDetectorConstruction();

    // Construct Functions
    G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField();

    // Update geometry
    void UpdateGeometry();

    // Set methods
    void SetWorldMat(G4String);
    void SetShieldMat(G4String);
    void SetDetMat(G4String);
		void SetScinMat(G4String);

    // Get methods
    G4Material* GetWorldMaterial()   const {return worldMat;};
    G4Material* GetShieldMaterial() const {return shieldMat;};
    G4Material* GetDetMaterial()     const {return detMat;};
    G4Material* GetScinMaterial()     const {return scinMat;};
		G4double 		GetDetSizeXY()			const {return detSizeXY;};
		G4double 		GetDetSizeZ()			const {return detSizeZ;};
		G4double 		GetScinRadIn()			const {return scinRadIn1;};
		G4double 		GetScinRadOut1()			const {return scinRadOut1;};
		G4double 		GetScinRadOut2()			const {return scinRadOut2;};
		G4double 		GetScinHeight()			const {return scinHeight;};
};
#endif

