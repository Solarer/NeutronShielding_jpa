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

#include "NSDetectorConstruction.hh"
#include "NSDetectorMessenger.hh"

#include "NSSD.hh"
#include "G4SDManager.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4VisAttributes.hh"

#include "G4RunManager.hh"

#include <string.h>
#include <stdio.h>

NSDetectorConstruction::NSDetectorConstruction()
: G4VUserDetectorConstruction(),
  world_mat   (0), shield_mat (0),  det_mat(0),
  solidWorld  (0), logicWorld  (0), physWorld  (0),
  solidShield(0), logicShield(0),
  solidDet    (0), logicDet    (0), physDet    (0)
{
  // Default parameters
  detRatio       = 0.5;
	shield_layer	 = 6;
  shieldBox_size[0] = 0.55*m;
  shieldBox_size[1] = 0.27*m;
  shieldBox_size[2] = 0.20*m;
	hSpace = 0.02*m; 
	vSpace = 0.02*m; 
	scin_height=0.70*m;
	scin_radius=0.10*m;
  ComputeParameters();

  // Default materials
  DefineMaterials();
  SetWorldMat("G4_AIR");
  SetShieldMat("G4_WATER");
  SetDetMat("lXe");
  SetScinMat("lXe");

  // Commands for interactive definition of detector
  fMessenger = new NSDetectorMessenger(this);
}

NSDetectorConstruction::~NSDetectorConstruction()
{
  delete fMessenger;
}

G4VPhysicalVolume* NSDetectorConstruction::Construct()
{
  return ConstructDetector();
}

void NSDetectorConstruction::DefineMaterials()
{
  // Get NIST manager
  G4NistManager* nistManager = G4NistManager::Instance();

  // Generic Materials defined from NIST database
  nistManager->FindOrBuildMaterial("G4_AIR");
  nistManager->FindOrBuildMaterial("G4_Galactic");

  // Shielding Materials

  // Materials defined from NIST database
  nistManager->FindOrBuildMaterial("G4_Pb");
  nistManager->FindOrBuildMaterial("G4_Fe");
  nistManager->FindOrBuildMaterial("G4_Cu");
  nistManager->FindOrBuildMaterial("G4_WATER");
  G4Material* polyethylene = nistManager->FindOrBuildMaterial("G4_POLYETHYLENE");

  // Boron defined as an element from isotopes
  G4double percentB10 = 19.9;
  G4Isotope* B10 = new G4Isotope("B10", 5, 10, 10.012937*g/mole);
  G4Isotope* B11 = new G4Isotope("B11", 5, 11, 11.009305*g/mole);
  G4Element* boron = new G4Element("boron", "B", 2);
  boron->AddIsotope(B10, percentB10*perCent);
  boron->AddIsotope(B11, (100-percentB10)*perCent);

  // Boron-doped polyethylene (BdP) defined as a material
  G4double densityBdP = 1.01*g/cm3;

  //generate a list of different dopes
  const double max_percentBdP=5.1;			// stepping: 0.1 , insert one step higher than required 	
  G4Material* BdP_List[int(max_percentBdP*10)]; 		

  for(double percentBdP = 0.0 ; percentBdP<max_percentBdP ; percentBdP+=0.1){
		char str[20];	
		sprintf(str,"%i_%i",int(percentBdP),int(percentBdP*10)%10);
  	BdP_List[int(percentBdP*10)] = new G4Material(std::string("BdP"+std::string(str)), densityBdP, 2);
  	BdP_List[int(percentBdP*10)]->AddElement(boron, percentBdP*perCent);
  	BdP_List[int(percentBdP*10)]->AddMaterial(polyethylene, (100-percentBdP)*perCent);
  }

  // Detector Materials

  // Liquid xenon defined as a material
  new G4Material("lXe", 54, 131.293*g/mole, 3*g/cm3);

  // Germanium defined from NIST database
  nistManager->FindOrBuildMaterial("G4_Ge");

  // Cesium iodide defined from elements
  G4Element* cesium = new G4Element("cesium", "Cs", 55, 132.90545*g/mole);
  G4Element* iodine = new G4Element("iodine", "I", 53, 126.90447*g/mole);
  G4double densityCsI = 4.510*g/cm3;
  G4Material* CsI = new G4Material("CsI", densityCsI, 2);
  CsI->AddElement(cesium, 1);
  CsI->AddElement(iodine, 1);

  // Liquid argon defined as a material
  new G4Material("lAr", 18, 39.948*g/mole, 1.40*g/cm3);

	// Scintilator Materials
	G4Material* scintillator = nistManager->FindOrBuildMaterial("G4_Ge");
	
	// create properties
	G4MaterialPropertiesTable *MPT = new G4MaterialPropertiesTable();

	G4int respElec = 11473.5;
	MPT->AddConstProperty("responseElectron",respElec);

	G4double arrayLen=28;
	G4double	respProtPos[] = {	0.1292866805*MeV,0.1686908915*MeV,0.1989778715*MeV,0.2390485181*MeV,0.3006683051*MeV,
															0.3387509159*MeV,0.3995706917*MeV,0.4800372072*MeV,0.5982633938*MeV,0.7187431277*MeV,
															0.8400454596*MeV,0.9908683037*MeV,1.292866805*MeV,1.7024552192*MeV,2.0081162226*MeV,
															2.390485181*MeV,3.0066830508*MeV,3.4187279441*MeV,3.9957069174*MeV,4.8003720719*MeV,
															6.0377690106*MeV,7.1874312769*MeV,8.4004545964,10*MeV,13.0478167493*MeV,
															17.0245521924*MeV,20.0811622263*MeV,24.1251554016*MeV,30.066830508*MeV,
															34.1872794405*MeV,40.3253076359*MeV};
	G4double respProtValue[] = {	224.0234814226,300.2583596286,351.5509357899,440.3881419004,
																590.2516122292,809.1396501575,1084.4887443223,1421.1564113641,
																1862.3388727039,2793.7269226247,4286.4122109316,5491.9430794436,
																7360.8436478874,10320.4499049279,12358.8060454755,15834.6551828443,
																20288.068591494,27192.0700304733,34063.5281434815,41720.7637851818,
																52263.6345732944,73277.50027919,100451.620481625,123032.420843188,
																154122.813204584,201968.554556124,236470.466441508,283174.925236377};
	MPT->AddProperty("responseProton",respProtPos,respProtValue,arrayLen);

	G4double	respAlphaPos[] = {	0.0990868304*MeV,0.1281060738*MeV,0.1686908915*MeV,0.1989778715*MeV,
																0.2390485181*MeV,0.3006683051*MeV,0.3387509159*MeV,0.3995706917*MeV,
																0.4800372072*MeV,0.5982633938*MeV,0.7187431277*MeV,0.8400454596*MeV,
																1	*MeV,1.3047816749*MeV,1.7024552192*MeV,1.9897787152*MeV,
																2.390485181*MeV,3.0066830508*MeV,3.3875091588*MeV,3.9592193355*MeV,
																4.8003720719*MeV,6.0377690106*MeV,7.1874312769*MeV,8.4004545964*MeV,
																10*MeV,12.9286680497*MeV,17.0245521924*MeV,20.0811622263*MeV,
																24.1251554016*MeV,30.066830508*MeV,33.8750915882*MeV,40.3253076359*MeV};
	G4double respAlphaValue[] = {	20.5641870723,26.3477564263,33.0058558079,38.6441846621,
																47.3311188778,60.6427468876,69.4204268699,83.1314137642,
																101.8187564769,130.4547457112,163.4207655764,200.1565759567,
																256.4495592205,367.7542750071,539.3842224631,675.6870521969,
																926.2578427625,1298.6823416662,1626.8604208953,2131.90144172,
																2989.084279467,4906.8451001206,7196.8567300115,10320.4499049279,
																15481.8863395872,27192.0700304732,46695.5967151881,62586.0431350512,
																87750.2843180668,120291.470422557,144049.820073016,176431.181504442};
	
	MPT->AddProperty("responseAlpha",respAlphaPos,respAlphaValue,arrayLen);

	G4double	respCarbonPos[] = {	0.0990868304*MeV,0.1281060738*MeV,0.1686908915*MeV,0.1989778715*MeV,
															0.2390485181*MeV,0.3006683051*MeV,0.3387509159*MeV,0.3995706917*MeV,
															0.4800372072*MeV,0.5982633938*MeV,0.7187431277*MeV,0.8400454596*MeV,
															1	*MeV,1.3047816749*MeV,1.7024552192*MeV,1.9897787152*MeV,
															2.390485181*MeV,3.0066830508*MeV,3.3875091588*MeV,3.9592193355*MeV,
															4.8003720719*MeV,6.0377690106*MeV,7.1874312769*MeV,8.4004545964*MeV,
															10*MeV,12.9286680497*MeV,17.0245521924*MeV,20.0811622263*MeV,
															24.1251554016*MeV,30.066830508*MeV,33.8750915882*MeV,40.3253076359*MeV};
	G4double respCarbonValue[] = {	12.812447355,15.3429892386,18.7919826474,22.5035217348,
																	25.7607737955,30.1614387878,33.7579242134,38.6441846621,
																	44.2377024948,54.1820192086,62.0245469604,67.8738593316,
																	77.698200196,97.3325982946,121.9286246899,139.5770740617,
																	163.4207655764,195.6974322018,224.0234814226,262.2929953739,
																	321.2545704722,376.1338902137,460.686078057,527.3676710427,
																	631.5262242549,827.5766320703,1160.3239495818,1389.4954943731,
																	1780.2837871681,2440.4816029045,2922.4926302337,3661.0088841166};
	MPT->AddProperty("responseCarbon",respCarbonPos,respCarbonValue,arrayLen);

	// Add properties to material
	scintillator->SetMaterialPropertiesTable(MPT);
}

G4VPhysicalVolume* NSDetectorConstruction::ConstructDetector()
{
  // Clean old geometry, if any
  G4GeometryManager::GetInstance()->OpenGeometry();
  G4PhysicalVolumeStore::GetInstance()->Clean();
  G4LogicalVolumeStore::GetInstance()->Clean();
  G4SolidStore::GetInstance()->Clean();

  // Complete parameters defintion
  ComputeParameters();

  // Option to switch on/off checking of volumes overlaps
  G4bool checkOverlaps = true;

  // World
  solidWorld =
    new G4Box("World",                          // name
              0.5*world_sizeXY,                 // size x
              0.5*world_sizeXY,                 // size y
              0.5*world_sizeZ);                 // size z

  logicWorld =
    new G4LogicalVolume(solidWorld,             // solid
                        world_mat,              // material
                        "World");               // name

  physWorld = 
    new G4PVPlacement(0,                        // no rotation
                      G4ThreeVector(),          // at (0,0,0)
                      logicWorld,               // logical volume
                      "World",                  // name
                      0,                        // mother  volume
                      false,                    // no boolean operation
                      0,                        // copy number
                      checkOverlaps);           // overlaps checking

  // Shield1
  solidShield =
    new G4Box("ShieldBox",                      // name
              0.5*shieldBox_size[0],            // size x
              0.5*shieldBox_size[1],            // size y 
              0.5*shieldBox_size[2]);            // size z

  logicShield =
    new G4LogicalVolume(solidShield,           // solid
                        shield_mat,            // material
                        "Shield");             // name



	// Prepare for turning boxes
	G4RotationMatrix* doRot = new G4RotationMatrix; 
	doRot->rotateZ(90*deg);
	G4RotationMatrix* doNotRot = new G4RotationMatrix; 
	doNotRot->rotateZ(0*deg);
	G4RotationMatrix* rotMat;


	// Place and turn them
	for (int shield_cnt=0 ; shield_cnt<shieldBox_number ; shield_cnt++)
		{
				if(shield_cnt%6 == 1 || shield_cnt%6 == 4 || shield_cnt>=shieldBox_number-4)
					rotMat=doRot;
				else
					rotMat=doNotRot;
		G4cout << "test";	
				physShield[shield_cnt] = 
					new G4PVPlacement(
										rotMat,                    		// rotation
                    shieldBox_position[shield_cnt],  	// at (0, 0, 0)
                    logicShield,               // logical volume
                    "Shield",                  // name
                    logicWorld,                 // mother volume
                    false,                      // no boolean operation
                    0,                          // copy number
                    checkOverlaps);             // overlaps checking    
		}


  // Detector
  solidDet =
    new G4Box("Det",                    // name
              detRatio*det_sizeXY,      // size x
              detRatio*det_sizeXY,      // size y
              detRatio*det_sizeZ);      // size z

  logicDet =
    new G4LogicalVolume(solidDet,               // solid
                        det_mat,                // material
                        "Det");                 // name

  physDet =
    new G4PVPlacement(0,                        // no rotation
                      G4ThreeVector(),          // at (0, 0, 0)
                      logicDet,                 // logical volume
                      "Det",                    // name
                      logicWorld,            		// mother volume
                      false,                    // no boolean operation
                      0,                        // copy number
                      checkOverlaps);           // overlaps checking


  // Szintillator 
  solidScin =
    new G4Tubs(	"Scin",                    	// name
								0,													// inner radius
								scin_radius,								// outer radius
								0.5*scin_height,								// heigth
								0,													// start angle
								360*deg);										// end angle
  logicScin =
    new G4LogicalVolume(solidScin,               // solid
                        scin_mat,                // material
                        "Scin");                 // name

  physScin=
    new G4PVPlacement(0,                        // no rotation
                      G4ThreeVector(),          // at (0, 0, 0)
                      logicScin,                // logical volume
                      "Scin",                   // name
                      logicDet,            			// mother volume
                      false,                    // no boolean operation
                      0,                        // copy number
                      checkOverlaps);           // overlaps checking


	// prepare and set visuable attributes
	G4VisAttributes visShield, visDet, visScin;
	visShield.SetColour(0,0,1);
	visDet.SetColour(1,1,0);
	visScin.SetColour(1,1,0);
	visScin.SetForceSolid(true);
 
	logicShield->SetVisAttributes(visShield);
	logicDet->SetVisAttributes(visDet);
	logicScin->SetVisAttributes(visScin);

  // Print volumes
  G4cout << "volumes: " << logicDet << " " << logicShield << " " << logicWorld << G4endl;

  // Make world box invisible
  logicWorld->SetVisAttributes (G4VisAttributes::Invisible);

  // Always return the physical World
  return physWorld;
}

void NSDetectorConstruction::ConstructSDandField()
{
  // Create new sensitive detector
  cennsSD = new NSSD("cennsSD", "CennsHitsCollection");

  // Assign sensitive detector to Det volume
  SetSensitiveDetector("Scin", cennsSD);
}

void NSDetectorConstruction::SetDetRatio(G4double ratio)
{
  // Check that detector has been constructed
  if (!solidDet) 
  {
    G4cerr << "Detector has not yet been constructed." << G4endl;
    return;
  }

  // Check that new detector ratio is between 0 and 1
  if (ratio < 0. || ratio > 1.)
  {
    G4cout << "Invalid detector ratio " << ratio
           << "!  No change to geometry." << G4endl;
    return;
  }

  // Set new detector ratio
  detRatio = ratio;

  G4cout << "Detector ratio set: " << detRatio << G4endl;
}

void NSDetectorConstruction::SetWorldMat(G4String materialChoice)
{
  // search the material by its name   
  G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);     
  if (pttoMaterial) world_mat = pttoMaterial;
}

void NSDetectorConstruction::SetShieldMat(G4String materialChoice)
{
  // search the material by its name   
  G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);     
  if (pttoMaterial) shield_mat = pttoMaterial;
}

void NSDetectorConstruction::SetDetMat(G4String materialChoice)
{
  // search the material by its name   
  G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);     
  if (pttoMaterial) det_mat = pttoMaterial;
}

void NSDetectorConstruction::SetScinMat(G4String materialChoice)
{
  // search the material by its name   
  G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);     
  if (pttoMaterial) scin_mat = pttoMaterial;
}

void NSDetectorConstruction::UpdateGeometry()
{
  // Completely reconstruct detector
  G4RunManager::GetRunManager()->DefineWorldVolume(ConstructDetector());

  // Reset sensitive detector
  SetSensitiveDetector("Det", cennsSD);
}

void NSDetectorConstruction::ComputeParameters()
{
  // These parameters are dependent upon other parameters and
  // must therefore be recalculated when the geometry is changed.
  world_sizeXY   = 20.0*m;
  world_sizeZ    = 20.0*m;
  det_sizeXY     = 1.0*m;
  det_sizeZ      = 1.0*m;
	shieldBox_number = shield_layer*6+4;
	shieldSize[0]	 = 2*shieldBox_size[0]+hSpace;
	shieldSize[1]	 = shieldBox_size[0]+2*shieldBox_size[1]+2*hSpace;
	shieldSize[2]	 = shield_layer == 0 ? 0 : shield_layer*shieldBox_size[2]+(shield_layer-1)*hSpace;

	physShield = new G4VPhysicalVolume*[shieldBox_number];
  shieldBox_position = new G4ThreeVector[shieldBox_number];
	
	// Positions and rotation of the shield boxes (first layer) 
	shieldBox_position[0].setX(0.5*hSpace+0.5*shieldBox_size[0]);
	shieldBox_position[0].setY(0.5*shieldBox_size[0]+hSpace+0.5*shieldBox_size[1]);
	shieldBox_position[0].setZ(0.5*shieldBox_size[2]-0.5*shieldSize[2]);
	
	shieldBox_position[1].setX(0.5*hSpace+shieldBox_size[0]-0.5*shieldBox_size[1]);
	shieldBox_position[1].setY(0.0);
	shieldBox_position[1].setZ(0.5*shieldBox_size[2]-0.5*shieldSize[2]);

	shieldBox_position[2].setX(shieldBox_position[0].getX());
	shieldBox_position[2].setY(-shieldBox_position[0].getY());
	shieldBox_position[2].setZ(0.5*shieldBox_size[2]-0.5*shieldSize[2]);

	shieldBox_position[3].setX(-shieldBox_position[0].getX());
	shieldBox_position[3].setY(-shieldBox_position[0].getY());
	shieldBox_position[3].setZ(0.5*shieldBox_size[2]-0.5*shieldSize[2]);

	shieldBox_position[4].setX(-shieldBox_position[1].getX());
	shieldBox_position[4].setY(0.0);
	shieldBox_position[4].setZ(0.5*shieldBox_size[2]-0.5*shieldSize[2]);

	shieldBox_position[5].setX(-shieldBox_position[0].getX());
	shieldBox_position[5].setY(shieldBox_position[0].getY());
	shieldBox_position[5].setZ(0.5*shieldBox_size[2]-0.5*shieldSize[2]);


	// calculate missing layers
	for (int currentLayer=1 ; currentLayer<shield_layer ; currentLayer++)
		for (int currentBox=0 ; currentBox<6 ; currentBox++)
			{
					shieldBox_position[currentBox+currentLayer*6]=shieldBox_position[currentBox];
					shieldBox_position[currentBox+currentLayer*6].setZ(shieldBox_position[0].getZ()+currentLayer*(shieldBox_size[2]+vSpace));
			}

	// top and bottom position
	// first box bottom
	shieldBox_position[shieldBox_number-4].setX(0.25*hSpace+0.5*shieldBox_size[1]);
	shieldBox_position[shieldBox_number-4].setY(0.0);
	shieldBox_position[shieldBox_number-4].setZ(-0.5*shieldSize[2]+0.5*shieldBox_size[2]);
	// second box bottom
	shieldBox_position[shieldBox_number-3].setX(-0.25*hSpace-0.5*shieldBox_size[1]);
	shieldBox_position[shieldBox_number-3].setY(0.0);
	shieldBox_position[shieldBox_number-3].setZ(-0.5*shieldSize[2]+0.5*shieldBox_size[2]);
	// first box top
	shieldBox_position[shieldBox_number-2]=shieldBox_position[shieldBox_number-4];
	shieldBox_position[shieldBox_number-2].setZ(0.5*shieldSize[2]-0.5*shieldBox_size[2]);
	// second box top
	shieldBox_position[shieldBox_number-1]=shieldBox_position[shieldBox_number-3];
	shieldBox_position[shieldBox_number-1].setZ(0.5*shieldSize[2]-0.5*shieldBox_size[2]);

	// and rotation
}

