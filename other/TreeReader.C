#define TreeReader_cxx
#include "TreeReader.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TPad.h>
TreeReader::TreeReader(std::string filename)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
	std::string tempFileName = filename;
      f = new TFile(tempFileName.c_str(),"UPDATE");
      while (!f->IsOpen()) 
				{
					delete f;
					f = NULL;
					std::cout << "File '" << tempFileName << "' not found. Please enter valid filename!" << std::endl;
					getline(cin,tempFileName);
      		f = new TFile(tempFileName.c_str(),"UPDATE");
      	}
      tree = (TTree*)gDirectory->Get("entered");
   	  Init(tree);
			Loop();
}

TreeReader::~TreeReader()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t TreeReader::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}

Long64_t TreeReader::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (!fChain->InheritsFrom(TChain::Class()))  return centry;
   TChain *chain = (TChain*)fChain;
   if (chain->GetTreeNumber() != fCurrent) {
      fCurrent = chain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void TreeReader::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);
   fChain->SetBranchAddress("Photons", &Photons, &b_Photons);
   fChain->SetBranchAddress("firstContact", &firstContact, &b_firstContact);
   Notify();
}

Bool_t TreeReader::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void TreeReader::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t TreeReader::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}

void TreeReader::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L TreeReader.C
//      Root > TreeReader t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//
   if (fChain == 0) return;

   fChain->SetBranchStatus("*",0);  // disable all branches
   fChain->SetBranchStatus("Photons",1);  // activate branchname
   fChain->SetBranchStatus("firstContact",1);  // activate branchname

   Long64_t nentries = fChain->GetEntriesFast();

	// create Histos
	TH1F* histEdep = new TH1F("histo_edep", "Energy deposition [keVee]", 60, 0, 600);
	TH1F* histTiming = new TH1F("histo_time", "Entering time", 100, 0, 200);

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) 
		{
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
			histEdep->Fill(Photons,0.1);
			histTiming->Fill(firstContact);
   	}
	gPad->SetLogY();
	histEdep->Write();
}

