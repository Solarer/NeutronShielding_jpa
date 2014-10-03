{
//=========Macro generated from canvas: c1/c1
//=========  (Fri Oct  3 14:21:17 2014) by ROOT version5.28/00c
   TCanvas *c1 = new TCanvas("c1", "c1",7,23,584,873);
   c1->Range(-1.3125,-3.236842,11.8125,27.02632);
   c1->SetFillColor(10);
   c1->SetBorderSize(2);
   c1->SetBottomMargin(0.14);
   
   TH2F *htemp__1 = new TH2F("htemp__1","percent:primaryEnergy",40,0,10.5,40,1,24);
   htemp__1->SetDirectory(0);
   htemp__1->SetStats(0);
   htemp__1->GetXaxis()->SetTitle("primaryEnergy");
   htemp__1->GetYaxis()->SetTitle("percent");
   htemp__1->Draw("");
   
   TPaveText *pt = new TPaveText(0.01,0.9434849,0.3673083,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   TText *text = pt->AddText("percent:primaryEnergy");
   pt->Draw();
   
   TGraph *graph = new TGraph(40);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetMarkerColor(3);
   graph->SetMarkerStyle(21);
   graph->SetPoint(0,10,22.55);
   graph->SetPoint(1,9.75,21.88);
   graph->SetPoint(2,9.5,21.92);
   graph->SetPoint(3,9.25,21.01);
   graph->SetPoint(4,9,21.05);
   graph->SetPoint(5,8.75,20.17);
   graph->SetPoint(6,8.5,20.29);
   graph->SetPoint(7,8.25,20.13);
   graph->SetPoint(8,8,20.4);
   graph->SetPoint(9,7.75,18.91);
   graph->SetPoint(10,7.5,20.05);
   graph->SetPoint(11,7.25,18.83);
   graph->SetPoint(12,7,19.62);
   graph->SetPoint(13,6.75,19.7);
   graph->SetPoint(14,6.5,19.75);
   graph->SetPoint(15,6.25,19.97);
   graph->SetPoint(16,6,19.61);
   graph->SetPoint(17,5.75,20.13);
   graph->SetPoint(18,5.5,20.29);
   graph->SetPoint(19,5.25,19.41);
   graph->SetPoint(20,5,19.74);
   graph->SetPoint(21,4.75,19.34);
   graph->SetPoint(22,4.5,19);
   graph->SetPoint(23,4.25,18.4);
   graph->SetPoint(24,4,19.67);
   graph->SetPoint(25,3.75,19.45);
   graph->SetPoint(26,3.5,19.15);
   graph->SetPoint(27,3.25,20.19);
   graph->SetPoint(28,3,19.93);
   graph->SetPoint(29,2.75,18.6);
   graph->SetPoint(30,2.5,20.52);
   graph->SetPoint(31,2.25,20.95);
   graph->SetPoint(32,2,19.96);
   graph->SetPoint(33,1.75,20.57);
   graph->SetPoint(34,1.5,20.63);
   graph->SetPoint(35,1.25,21.79);
   graph->SetPoint(36,1,20.59);
   graph->SetPoint(37,0.75,20.33);
   graph->SetPoint(38,0.5,20.2);
   graph->SetPoint(39,0.25,2.11);
   
   TH1F *Graph_Graph1 = new TH1F("Graph_Graph1","Graph",100,0,10.975);
   Graph_Graph1->SetMinimum(0.066);
   Graph_Graph1->SetMaximum(24.594);
   Graph_Graph1->SetDirectory(0);
   Graph_Graph1->SetStats(0);
   graph->SetHistogram(Graph_Graph1);
   
   graph->Draw("p");
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
