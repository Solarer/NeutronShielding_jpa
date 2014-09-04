#include "TROOT.h"
#include "TString.h"
#include "TFile.h"
#include "TH1.h"
#include "TPie.h"
#include "TPieSlice.h"
#include "TLegend.h"
#include "TCanvas.h"

#include "TTree.h"
#include <iostream>
#include <stdlib.h>




void piechart()
{
   Float_t vals[] = {5787.18,30957.81,2565554.97,15505.75,1306.94,558247.311,1312.98};
   Int_t colors[] = {2,3,4,5,6,7,8};
   Int_t nvals = sizeof(vals)/sizeof(vals[0]);

   TCanvas *cpie = new TCanvas("cpie","TPie test",700,700);

   TPie *pie = new TPie("pie",
      "Pie with verbose labels",nvals,vals,colors);

   //pie->SetRadius(.2);
   //pie->SetLabelsOffset(.01);
   //pie->SetLabelFormat("#splitline{%val (%perc)}{%txt}");

	pie->SetY(.32);
   pie->GetSlice(0)->SetValue(.8);
   pie->GetSlice(1)->SetFillStyle(3031);
   pie->SetLabelsOffset(-.1);
   pie->Draw("3d t nol");
   TLegend *pieleg = pie->MakeLegend();
   pieleg->SetY1(.56); pieleg->SetY2(.86);
   pie->Draw("nol <");
}
