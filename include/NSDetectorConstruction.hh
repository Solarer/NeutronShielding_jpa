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

class G4Material;
class G4Element;
class G4Box;
class G4LogicalVolume;
class G4VPhysicalVolume;
class NSDetectorMessenger;
class NSSD;

class NSDetectorConstruction : public G4VUserDetectorConstruction
{
  public:

    NSDetectorConstruction();
   ~NSDetectorConstruction();

  public:

    // Set methods

    void SetDetRatio     (G4double);
    void SetShieldBoxSize  (G4double,G4double,G4double);
    void SetShieldBoxMat (G4double,G4double,G4double);
    void SetWorldMat     (G4String);
    void SetShieldMat     (G4String);
    void SetDetMat       (G4String);

    // Construct Functions
    G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField();

    // Update geometry
    void UpdateGeometry();

    // Get methods

    G4double    GetDetRatio()        const {return detRatio;};
    // G4double    GetWaterBoxSizeX()   const {return waterBox_sizeX;};
    // G4double    GetShieldLayer()   const {return det_layer;};
    G4Material* GetWorldMaterial()   const {return world_mat;};
    G4Material* GetShieldMaterial() const {return shield_mat;};
    G4Material* GetDetMaterial()     const {return det_mat;};

  private:

    // Data members

    G4Material* world_mat;
    G4Material* shield_mat;
    G4Material* det_mat;

    G4double world_sizeXY, world_sizeZ;
    G4double detRatio, det_sizeXY, det_sizeZ;

		int shield_layer;																			// number of layer
		int shieldBox_number;														// total number of boxes
    G4double shieldBox_size[3];														// size of box (length,width,height)
		G4double hSpace, vSpace;															// some space between the boxes
		G4ThreeVector* shieldBox_position;										// box positions

    G4Box*             solidWorld;
    G4LogicalVolume*   logicWorld;
    G4VPhysicalVolume* physWorld;

    G4Box*             solidShield1;
    G4LogicalVolume*   logicShield1;
    G4VPhysicalVolume* physShield1; 

    G4Box*             solidDet;
    G4LogicalVolume*   logicDet;
    G4VPhysicalVolume* physDet;

    NSDetectorMessenger* fMessenger;  // Pointer to messenger
    NSSD* cennsSD;                    // Pointer to sensitive detector

    // Methods

    void DefineMaterials();
    void ComputeParameters();
    G4VPhysicalVolume* ConstructDetector();
};

#endif

