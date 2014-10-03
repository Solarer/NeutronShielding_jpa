//
// This macro fills a tree with
// the data from NS.out.
//

int TreeMac()
{
  Int_t runID;
  Int_t entries;
  Double_t primaryEnergy;
  Double_t shieldSizeXY;
  Double_t percentBdP;
  Char_t worldMat;
  Char_t shieldMat;
  Char_t detMat;
  Char_t scinMat;
  Double_t meanEdep;
  Double_t percent;
  Double_t percent2;
  Double_t rmsPercent;

  // Open input text file
  TString dir = gSystem->UnixPathName(gInterpreter->GetCurrentMacroName());
  dir.ReplaceAll("TreeMac.C","");
  dir.ReplaceAll("/./","/");
  FILE *fp = fopen(Form("%sNS.out",dir.Data()),"r");

  // Open root output file
  TString filename = "NS.root";
  TFile *hfile = TFile::Open(filename,"RECREATE");

  // Declare tree and branches
  TTree *tree = new TTree("tree","Run Information");
  tree->Branch("runID", &runID, "runID/I");
  tree->Branch("entries", &entries, "entries/I");
  tree->Branch("primaryEnergy", &primaryEnergy, "primaryEnergy/D");
  tree->Branch("shieldSizeXY", &shieldSizeXY, "shieldSizeXY/D");
  tree->Branch("percentBdP", &percentBdP, "percentBdP/D");
  tree->Branch("worldMat", worldMat, "worldMat/C");
  tree->Branch("shieldMat", shieldMat, "shieldMat/C");
  tree->Branch("detMat", detMat, "detMat/C");
  tree->Branch("scinMat", scinMat, "scinMat/C");
  tree->Branch("meanEdep", &meanEdep, "meanEdep/D");
  tree->Branch("percent", &percent, "percent/D");
  tree->Branch("rmsPercent", &rmsPercent, "rmsPercent/D");
  tree->Branch("percent2", &percent2, "percent2/D");


  // Fill tree
  Long64_t nlines = tree->ReadFile("NS.out_richtig_energies100",
    "runID/I:entries/I:primaryEnergy/D:shieldSizeXY/D:percentBdP/D:"
    "worldMat/C:shieldMat/C:detMat/C:scinMat/C:meanEdep/D:percent/D:rmsPercent/D:percent2/D");

  // Write tree
  tree->Write();

  // Close input file
  fclose(fp);

	cout << "Read " << nlines << " lines" << std::endl;
  // Free output file pointer
  delete hfile;

  return nlines;
}
