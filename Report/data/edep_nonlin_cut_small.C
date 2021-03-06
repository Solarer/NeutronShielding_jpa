{
//=========Macro generated from canvas: c1/c1
//=========  (Fri Oct  3 10:41:11 2014) by ROOT version5.28/00c
   TCanvas *c1 = new TCanvas("c1", "c1",7,23,1600,873);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   c1->Range(-129.7297,-1.400806,681.0811,1.799516);
   c1->SetFillColor(10);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetLogy();
   c1->SetTickx(1);
   c1->SetTicky(1);
   c1->SetLeftMargin(0.16);
   c1->SetBottomMargin(0.16);
   c1->SetFrameLineWidth(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameLineWidth(2);
   c1->SetFrameBorderMode(0);
   
   TH1D *histo_edep = new TH1D("histo_edep","Energy deposition [keVee]",60,0,600);
   histo_edep->SetBinContent(4,15.9197);
   histo_edep->SetBinContent(5,12.15869);
   histo_edep->SetBinContent(6,10.76625);
   histo_edep->SetBinContent(7,9.356589);
   histo_edep->SetBinContent(8,7.629204);
   histo_edep->SetBinContent(9,6.525783);
   histo_edep->SetBinContent(10,5.506578);
   histo_edep->SetBinContent(11,4.64145);
   histo_edep->SetBinContent(12,4.276833);
   histo_edep->SetBinContent(13,3.821301);
   histo_edep->SetBinContent(14,3.462426);
   histo_edep->SetBinContent(15,3.160014);
   histo_edep->SetBinContent(16,2.960958);
   histo_edep->SetBinContent(17,2.718837);
   histo_edep->SetBinContent(18,2.527437);
   histo_edep->SetBinContent(19,2.28723);
   histo_edep->SetBinContent(20,2.213541);
   histo_edep->SetBinContent(21,2.051808);
   histo_edep->SetBinContent(22,2.062335);
   histo_edep->SetBinContent(23,1.834569);
   histo_edep->SetBinContent(24,1.824042);
   histo_edep->SetBinContent(25,1.541727);
   histo_edep->SetBinContent(26,1.460382);
   histo_edep->SetBinContent(27,1.436457);
   histo_edep->SetBinContent(28,1.327359);
   histo_edep->SetBinContent(29,1.252713);
   histo_edep->SetBinContent(30,1.175196);
   histo_edep->SetBinContent(31,1.073754);
   histo_edep->SetBinContent(32,1.060356);
   histo_edep->SetBinContent(33,1.031646);
   histo_edep->SetBinContent(34,1.001979);
   histo_edep->SetBinContent(35,0.914892);
   histo_edep->SetBinContent(36,0.863214);
   histo_edep->SetBinContent(37,0.837375);
   histo_edep->SetBinContent(38,0.792396);
   histo_edep->SetBinContent(39,0.740718);
   histo_edep->SetBinContent(40,0.677556);
   histo_edep->SetBinContent(41,0.614394);
   histo_edep->SetBinContent(42,0.654588);
   histo_edep->SetBinContent(43,0.624921);
   histo_edep->SetBinContent(44,0.579942);
   histo_edep->SetBinContent(45,0.514866);
   histo_edep->SetBinContent(46,0.493812);
   histo_edep->SetBinContent(47,0.500511);
   histo_edep->SetBinContent(48,0.462231);
   histo_edep->SetBinContent(49,0.43065);
   histo_edep->SetBinContent(50,0.431607);
   histo_edep->SetBinContent(51,0.40194);
   histo_edep->SetBinContent(52,0.341649);
   histo_edep->SetBinContent(53,0.360789);
   histo_edep->SetBinContent(54,0.333993);
   histo_edep->SetBinContent(55,0.307197);
   histo_edep->SetBinContent(56,0.320595);
   histo_edep->SetBinContent(57,0.289014);
   histo_edep->SetBinContent(58,0.294756);
   histo_edep->SetBinContent(59,0.299541);
   histo_edep->SetBinContent(60,0.25839);
   histo_edep->SetEntries(139403);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#0000ff");
   histo_edep->SetLineColor(ci);
   histo_edep->SetLineWidth(2);
   histo_edep->GetXaxis()->SetTitle("energy deposition [keVee]");
   histo_edep->GetXaxis()->CenterTitle(true);
   histo_edep->GetXaxis()->SetNdivisions(506);
   histo_edep->GetXaxis()->SetLabelFont(42);
   histo_edep->GetXaxis()->SetLabelSize(0.06);
   histo_edep->GetXaxis()->SetTitleSize(0.06);
   histo_edep->GetXaxis()->SetTitleFont(42);
   histo_edep->GetYaxis()->SetTitle("count / 10 keVee / 60 days");
   histo_edep->GetYaxis()->CenterTitle(true);
   histo_edep->GetYaxis()->SetNdivisions(506);
   histo_edep->GetYaxis()->SetLabelFont(42);
   histo_edep->GetYaxis()->SetLabelSize(0.06);
   histo_edep->GetYaxis()->SetTitleSize(0.06);
   histo_edep->GetYaxis()->SetTitleOffset(1.05);
   histo_edep->GetYaxis()->SetTitleFont(42);
   histo_edep->GetZaxis()->SetLabelFont(42);
   histo_edep->GetZaxis()->SetLabelSize(0.06);
   histo_edep->GetZaxis()->SetTitleSize(0.07);
   histo_edep->GetZaxis()->SetTitleFont(42);
   histo_edep->Draw("");
   
   TLegend *leg = new TLegend(0.5,0.7,0.9,0.9,NULL,"brNDC");
   leg->SetBorderSize(1);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(10);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("histo_edep","Geant4 non-linear and 5 #mus cutoff","l");

   ci = TColor::GetColor("#0000ff");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   leg->Draw();
   
   TPaveText *pt = new TPaveText(0.2140204,0.9081818,0.7859796,0.99,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   TText *text = pt->AddText("Energy deposition [keVee]");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
