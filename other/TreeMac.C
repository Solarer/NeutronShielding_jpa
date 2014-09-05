//
// This macro fills a tree with
// the data from NS.out.
//

int main()
{
  Int_t runID;
  Double_t ke;
  Double_t shield1_sizexy;
  Double_t shield2Ratio;
  Double_t detRatio;
  Double_t percentBdP;
  Char_t world_mat;
  Char_t shield1_mat;
  Char_t shield2_mat;
  Char_t det_mat;
  Double_t meanEdep;
  Double_t percent;

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
  tree->Branch("ke", &ke, "ke/D");
  tree->Branch("shield1_sizexy", &shield1_sizexy, "shield1_sizexy/D");
  tree->Branch("shield2Ratio", &shield2Ratio, "shield2Ratio/D");
  tree->Branch("detRatio", &detRatio, "detRatio/D");
  tree->Branch("percentBdP", &percentBdP, "percentBdP/D");
  tree->Branch("world_mat", world_mat, "world_mat/C");
  tree->Branch("shield1_mat", shield1_mat, "shield1_mat/C");
  tree->Branch("shield2_mat", shield2_mat, "shield2_mat/C");
  tree->Branch("det_mat", det_mat, "det_mat/C");
  tree->Branch("meanEdep", &meanEdep, "meanEdep/D");
  tree->Branch("percent", &percent, "percent/D");

  // Fill tree
  Long64_t nlines = tree->ReadFile("NS.out",
    "runID/I:ke/D:shield1_sizexy/D:shield2Ratio/D:detRatio/D:percentBdP/D:"
    "world_mat/C:shield1_mat/C:shield2_mat/C:det_mat/C:meanEdep/D:percent/D");

  // Write tree
  tree->Write();

  // Close input file
  fclose(fp);

  // Free output file pointer
  delete hfile;

  return 0;
}
