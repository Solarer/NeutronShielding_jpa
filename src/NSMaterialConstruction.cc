
#include "NSDetectorConstruction.hh"
#include "G4SystemOfUnits.hh"
#include "G4NistManager.hh"

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

  // Lead defined from NIST database
  nistManager->FindOrBuildMaterial("G4_Pb");

  // Cesium iodide defined from elements
  G4Element* cesium = new G4Element("cesium", "Cs", 55, 132.90545*g/mole);
  G4Element* iodine = new G4Element("iodine", "I", 53, 126.90447*g/mole);
  G4double densityCsI = 4.510*g/cm3;
  G4Material* CsI = new G4Material("CsI", densityCsI, 2);
  CsI->AddElement(cesium, 1);
  CsI->AddElement(iodine, 1);

  // Liquid argon defined as a material
  new G4Material("lAr", 18, 39.948*g/mole, 1.40*g/cm3);

	// Scintillator Materials
	G4Material* EJ301 = new G4Material("EJ301",0.87*g/cm3, 2, kStateLiquid);
  G4Element* carbon = new G4Element("carbon", "C", 6, 12.0107*g/mole);
  G4Element* hydrogen = new G4Element("hydrogen", "H", 1, 1.00794*g/mole);
	EJ301->AddElement(carbon,8);
	EJ301->AddElement(hydrogen,10);
	
	// create properties with photon response
	G4MaterialPropertiesTable *MPT = new G4MaterialPropertiesTable();

	G4double respElec = 11499.9/MeV;
	MPT->AddConstProperty("responseElectron",respElec);

	G4double respDeut = 2860.1325/MeV;
	MPT->AddConstProperty("responseDeuteron",respDeut);

	G4int arrayLen = 32;
	G4double	respProtPos[] = {	0.1*MeV, 				0.1292866805*MeV,0.1686908915*MeV,0.1989778715*MeV,0.2390485181*MeV,
															0.3006683051*MeV,0.3387509159*MeV,0.3995706917*MeV,0.4800372072*MeV,
															0.5982633938*MeV,0.7187431277*MeV,0.8400454596*MeV,0.9908683037*MeV,
															1.292866805*MeV,1.7024552192*MeV,2.0081162226*MeV,2.390485181*MeV,
															3.0066830508*MeV,3.4187279441*MeV,3.9957069174*MeV,4.8003720719*MeV,
															6.0377690106*MeV,7.1874312769*MeV,8.4004545964*MeV,10*MeV,
															13.0478167493*MeV,17.0245521924*MeV,20.0811622263*MeV,24.1251554016*MeV,
															30.066830508*MeV,34.1872794405*MeV,40.3253076359*MeV};
	G4double respProtValue[] = {	83.1314137642,108.9386517613,146.0103229816,174.8483136869,
																224.0234814226,300.2583596286,351.5509357899,440.3881419004,
																590.2516122292,809.1396501575,1084.4887443223,1421.1564113641,
																1862.3388727039,2793.7269226247,4286.4122109316,5491.9430794436,
																7360.8436478874,10320.4499049279,12358.8060454755,15834.6551828443,
																20288.068591494,27192.0700304733,34063.5281434815,41720.7637851818,
																52263.6345732944,73277.50027919,100451.620481625,123032.420843188,
																154122.813204584,201968.554556124,236470.466441508,283174.925236377};
	MPT->AddProperty("responseProton",respProtValue,respProtPos,arrayLen);

	G4double	respAlphaPos[] = {	0.0990868304*MeV,0.1281060738*MeV,0.1686908915*MeV,0.1989778715*MeV,
																0.2390485181*MeV,0.3006683051*MeV,0.3387509159*MeV,0.3995706917*MeV,
																0.4800372072*MeV,0.5982633938*MeV,0.7187431277*MeV,0.8400454596*MeV,
																1.	*MeV,				1.3047816749*MeV,1.7024552192*MeV,1.9897787152*MeV,
																2.390485181*MeV,3.0066830508*MeV,3.3875091588*MeV,3.9592193355*MeV,
																4.8003720719*MeV,6.0377690106*MeV,7.1874312769*MeV,8.4004545964*MeV,
																10*MeV,					12.9286680497*MeV,17.0245521924*MeV,20.0811622263*MeV,
																24.1251554016*MeV,30.066830508*MeV,33.8750915882*MeV,40.3253076359*MeV};
	G4double respAlphaValue[] = {	20.5641870723,26.3477564263,33.0058558079,38.6441846621,
																47.3311188778,60.6427468876,69.4204268699,83.1314137642,
																101.8187564769,130.4547457112,163.4207655764,200.1565759567,
																256.4495592205,367.7542750071,539.3842224631,675.6870521969,
																926.2578427625,1298.6823416662,1626.8604208953,2131.90144172,
																2989.084279467,4906.8451001206,7196.8567300115,10320.4499049279,
																15481.8863395872,27192.0700304732,46695.5967151881,62586.0431350512,
																87750.2843180668,120291.470422557,144049.820073016,176431.181504442};
	MPT->AddProperty("responseAlpha",respAlphaValue,respAlphaPos,arrayLen);

	G4double	respCarbonPos[] = {		0.0990868304	*MeV,0.1281060738	*MeV,0.1686908915	*MeV,0.1989778715	*MeV,
																	0.2390485181	*MeV,0.2952021539	*MeV,0.3356575454	*MeV,0.3923064947	*MeV,
																	0.4713101285	*MeV,0.5928002342	*MeV,0.7056763743	*MeV,0.8400454596	*MeV,
																	1.*MeV,1.292866805	*MeV,1.7024552192	*MeV,1.9897787152	*MeV,
																	2.4125155402	*MeV,3.0066830508	*MeV,3.4187279441	*MeV,3.9957069174	*MeV,
																	4.8003720719	*MeV,6.0377690106	*MeV,7.1874312769	*MeV,8.4004545964	*MeV,
																	10.	*MeV,13.0478167493	*MeV,17.1814479567	*MeV,20.0811622263	*MeV,
																	23.9048518099	*MeV,30.066830508	*MeV,34.1872794405	*MeV,40.3253076359	*MeV};

	G4double respCarbonValue[] = {	12.812447355,15.3429892386,18.7919826474,22.5035217348,
																	25.7607737955,30.1614387878,33.7579242134,38.6441846621,
																	44.2377024948,54.1820192086,62.0245469604,67.8738593316,
																	77.698200196,97.3325982946,121.9286246899,139.5770740617,
																	163.4207655764,195.6974322018,224.0234814226,262.2929953739,
																	321.2545704722,376.1338902137,460.686078057,527.3676710427,
																	631.5262242549,827.5766320703,1160.3239495818,1389.4954943731,
																	1780.2837871681,2440.4816029045,2922.4926302337,3661.0088841166};
	MPT->AddProperty("responseCarbon",respCarbonValue,respCarbonPos,arrayLen);

	// Add properties to material
	G4Material::GetMaterial("EJ301")->SetMaterialPropertiesTable(MPT);
}

void NSDetectorConstruction::CalcSlopes(G4double* pos, G4double* value, G4int length)
{
	// create 2 temp arrays
	G4double* temp_pos = new G4double[length-1];
	G4double* temp_value = new G4double[length-1];

	// fill them with slopes
	for(int i=0 ; i<length-1 ; i++)
	{
		temp_pos[i] = (pos[i]+pos[i+1])/2;
		temp_value[i] = (value[i]+value[i+1])/2;
	}
		
	// assign new values
	pos = temp_pos;
	value = temp_value;
}
