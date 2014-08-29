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
#include "G4Tubs.hh"

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
    G4Material* world_mat;
    G4Material* shield_mat;
    G4Material* det_mat;
    G4Material* scin_mat;

		// Sizes

		// world
    G4double world_sizeXY, world_sizeZ;

		// lead
    G4double det_sizeXY, det_sizeZ, detRatio;

		// water shielding
		int shield_layer;												// number of layer
		G4double shieldSize[3];
		int shieldBox_number;										// total number of boxes
    G4double shieldBox_size[3];							// size of box (length,width,height)
		G4double hSpace, vSpace;								// some space between the boxes
		G4ThreeVector* shieldBox_position;			// box positions

		// scintillator
		G4double scin_radius, scin_radiusRatio;
		G4double scin_height, scin_heightRatio;

		// Volumes

    G4Box*             solidWorld;
    G4LogicalVolume*   logicWorld;
    G4VPhysicalVolume* physWorld;

    G4Box*             solidShield;
    G4LogicalVolume*   logicShield;
    G4VPhysicalVolume**  physShield; 

    G4Box*             solidDet;
    G4LogicalVolume*   logicDet;
    G4VPhysicalVolume* physDet;

    G4Tubs*            solidScin;
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
    void SetDetRatio     (G4double);
    void SetShieldBoxSize  (G4double,G4double,G4double);
    void SetShieldBoxMat (G4double,G4double,G4double);
    void SetWorldMat     (G4String);
    void SetShieldMat     (G4String);
    void SetDetMat       (G4String);
		void SetScinMat(G4String);

    // Get methods
    G4Material* GetWorldMaterial()   const {return world_mat;};
    G4Material* GetShieldMaterial() const {return shield_mat;};
    G4Material* GetDetMaterial()     const {return det_mat;};
    G4double    GetDetRatio()        const {return detRatio;};
		G4ThreeVector* GetShieldBoxPosition() const {return shieldBox_position;};
    G4double    GetShieldBoxNumber()   const {return shieldBox_number;};
    G4double    GetShieldBoxSizeX()   const {return shieldBox_size[0];};
    G4double    GetShieldBoxSizeY()   const {return shieldBox_size[1];};
    G4double    GetShieldBoxSizeZ()   const {return shieldBox_size[2];};
		G4double 		GetDetSizeXY()			const {return det_sizeXY;};
		G4double 		GetDetSizeZ()			const {return det_sizeZ;};
		G4double 		GetScinRad()			const {return scin_radius;};
		G4double 		GetScinHeight()			const {return scin_height;};
};
#endif

