#include "TString.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TPie.h"
#include "TPieSlice.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TMarker.h"


#include "TTree.h"
#include <iostream>
#include <stdlib.h>

void test() {
   TFile *f = new TFile("singleRun_10MeV_Water.root");
   TTree *T = (TTree*)f->Get("singleRun");
   TCanvas *c1 = new TCanvas("c1");
   //T->Draw("Photons:Edep");
   //h->Draw();
   //c1->Update();
   //T->SetMarkerStyle(3);
   //TCanvas *c1 = new TCanvas("c1","A Simple Graph Example",200,10,700,500);

	Long64_t nentries = T->GetEntries();

	Double_t x[1000000];
	Double_t y[1000000];

	Double_t fEdep;
	Double_t fPhotons;

	T->SetBranchAddress("Edep",&fEdep);
	T->SetBranchAddress("Photons",&fPhotons);

   for (Int_t i=0;i<nentries;i++) {
		T->GetEntry(i);
     x[i] = fEdep;
     y[i] = fPhotons;
   }
cout << "files read"<<std::endl;
   gr = new TGraph(nentries,x,y);
		c1->SetLogy();
		c1->SetLogx();
	gr->GetYaxis()->SetRangeUser(10,1000000);
	gr->GetXaxis()->SetRangeUser(0.1,100);
	gr->SetMarkerStyle(1);
   gr->Draw("AP");
}
