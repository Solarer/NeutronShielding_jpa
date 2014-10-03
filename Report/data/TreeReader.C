#define TreeReader_cxx
#include "TreeReader.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TPad.h>
TreeReader::TreeReader()
{
			std::string tempFileName = "singleRun_MCNP.root";
      f = new TFile(tempFileName.c_str(),"UPDATE");
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
   if (fChain == 0) return;

   fChain->SetBranchStatus("*",0);  // disable all branches
   fChain->SetBranchStatus("Photons",1);  // activate branchname
   fChain->SetBranchStatus("firstContact",1);  // activate branchname

   Long64_t nentries = fChain->GetEntriesFast();

	// create Histos
	TCanvas* c1 = new TCanvas();
  c1->SetLogy();

cout << "ok1"<< std::endl;

	TH1D* histEdep = new TH1D("histo_edep", "Energy deposition [keVee]", 60, 0, 600);
	TH1D* histEdep_full = new TH1D("histEdep_full", "Energy deposition [keVee]", 600, 0, 6.);
	TH1D* histTiming = new TH1D("histo_time", "Entime", 100, 0, 200);
	TH1D *histEdep2 = new TH1D("histo_edep","Energy deposition [keVee]",60,0,600);

cout << "ok2"<< std::endl;
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) 
		{
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

			histEdep_full->Fill(Photons/1000);

      if(Photons<=600)
			{
				histEdep->Fill(Photons);
				histTiming->Fill(firstContact);
			}
   	}
cout << "ok3"<< std::endl;
	//3,4*10**-10 => 29
	double total=1000000;
	double scale = 1./total*29*0.55*60;
	histEdep->Scale(scale);
	histEdep->GetYaxis()->SetRangeUser(0.001, 100.);
	//histEdep->Draw();
	
	histEdep_full->Scale(scale);
	histEdep_full->Draw();
	
cout << "ok4"<< std::endl;


double values[] ={
0,0,0,0.00,13.91,11.93,10.66,8.84,8.07,6.33,5.55,5.10,4.35,4.11,3.61,3.03,2.69,2.16,2.26,1.89,1.86,1.50,1.46,1.65,1.25,1.01,0.98,0.74,0.66,0.62,0.55,0.51,0.54,0.42,
0.49,0.33,0.32,0.26,0.28,0.27,0.26,0.17,0.20, 0.19, 0.18, 0.21, 0.19, 0.18, 0.14, 0.09, 0.19, 0.14, 0.12, 0.10, 0.08, 0.07, 0.12, 0.03, 0.05, 0.02, 0.05};

	for(int i=1; i<=60; i++)
  	histEdep2->SetBinContent(i,values[i]);
  
  //histo_edep->SetMinimum(0.001);
  //histo_edep->SetMaximum(100);
	histEdep2->SetLineColor(2);
	//histo_edep->Draw("same");


cout << "ok5"<< std::endl;
	// Legend
	TLegend* leg = new TLegend(0.5,0.7,0.9,0.9);
	leg->SetBorderSize(1);
  //leg->AddEntry(histEdep2,"MCNP","l");
  leg->AddEntry(histEdep,"Geant4 linear energy deposition","l");
  leg->Draw("same");


	// Draw all
	//c1->Draw();
}

