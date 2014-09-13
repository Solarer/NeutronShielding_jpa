{
//=========Macro generated from canvas: Canvas 1/Canvas 1
//=========  (Fri Sep 12 14:57:47 2014) by ROOT version5.28/00c
   TCanvas *Canvas = new TCanvas("Canvas 1", "Canvas 1",251,104,1490,853);
   Canvas->Range(-0.8464256,-689.8062,7.652145,4222.813);
   Canvas->SetFillColor(10);
   Canvas->SetBorderSize(2);
   Canvas->SetBottomMargin(0.1404151);
   
   TH1F *htemp__1 = new TH1F("htemp__1","primEnergy",100,0,6.8);
   htemp__1->SetBinContent(4,2267);
   htemp__1->SetBinContent(12,3559);
   htemp__1->SetBinContent(19,2348);
   htemp__1->SetBinContent(26,1817);
   htemp__1->SetBinContent(34,1305);
   htemp__1->SetBinContent(41,1012);
   htemp__1->SetBinContent(48,740);
   htemp__1->SetBinContent(56,464);
   htemp__1->SetBinContent(63,255);
   htemp__1->SetBinContent(70,139);
   htemp__1->SetBinContent(78,79);
   htemp__1->SetBinContent(85,51);
   htemp__1->SetBinContent(92,26);
   htemp__1->SetEntries(14062);
   htemp__1->SetDirectory(0);
   
   TPaveStats *ptstats = new TPaveStats(0.6,0.7,0.9,0.9,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(10);
   ptstats->SetTextAlign(12);
   TText *text = ptstats->AddText("htemp");
   text->SetTextSize(0.046);
   text = ptstats->AddText("Entries = 14062  ");
   text = ptstats->AddText("Mean  =  1.552");
   text = ptstats->AddText("RMS   =  1.154");
   ptstats->SetOptStat(1111);
   ptstats->SetOptFit(0);
   ptstats->Draw();
   htemp__1->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(htemp__1->GetListOfFunctions());
   htemp__1->SetFillStyle(101);
   htemp__1->GetXaxis()->SetTitle("primEnergy");
   htemp__1->GetXaxis()->SetRange(0,50);
   htemp__1->Draw("");
   
   TPaveText *pt = new TPaveText(0.01,0.9422528,0.1719919,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   text = pt->AddText("primEnergy");
   pt->Draw();
   Canvas->Modified();
   Canvas 1->cd();
   Canvas 1->SetSelected(Canvas 1);
   Canvas 1->ToggleToolBar();
}
