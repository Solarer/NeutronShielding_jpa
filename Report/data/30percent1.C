{
//=========Macro generated from canvas: c1/c1
//=========  (Thu Oct  2 22:05:13 2014) by ROOT version5.28/00c
   TCanvas *c1 = new TCanvas("c1", "c1",7,23,1393,873);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   c1->Range(-2.27027,-4.236842,11.91892,26.02632);
   c1->SetFillColor(10);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetTickx(1);
   c1->SetTicky(1);
   c1->SetLeftMargin(0.16);
   c1->SetBottomMargin(0.14);
   c1->SetFrameLineWidth(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameLineWidth(2);
   c1->SetFrameBorderMode(0);
   
   TH2F *htemp__1__1__2__1 = new TH2F("htemp__1__1__2__1","",40,0,10.5,40,0,23);
   htemp__1__1__2__1->SetDirectory(0);
   htemp__1__1__2__1->SetStats(0);
   htemp__1__1__2__1->SetLineColor(4);
   htemp__1__1__2__1->SetLineWidth(2);
   htemp__1__1__2__1->GetXaxis()->SetTitle("neutron energy [MeV]");
   htemp__1__1__2__1->GetXaxis()->SetNdivisions(506);
   htemp__1__1__2__1->GetXaxis()->SetLabelFont(42);
   htemp__1__1__2__1->GetXaxis()->SetLabelSize(0.06);
   htemp__1__1__2__1->GetXaxis()->SetTitleSize(0.06);
   htemp__1__1__2__1->GetXaxis()->SetTitleFont(42);
   htemp__1__1__2__1->GetYaxis()->SetTitle("efficiency [%]");
   htemp__1__1__2__1->GetYaxis()->CenterTitle(true);
   htemp__1__1__2__1->GetYaxis()->SetNdivisions(506);
   htemp__1__1__2__1->GetYaxis()->SetLabelFont(42);
   htemp__1__1__2__1->GetYaxis()->SetLabelSize(0.06);
   htemp__1__1__2__1->GetYaxis()->SetTitleSize(0.06);
   htemp__1__1__2__1->GetYaxis()->SetTitleOffset(0.95);
   htemp__1__1__2__1->GetYaxis()->SetTitleFont(42);
   htemp__1__1__2__1->GetZaxis()->SetLabelFont(42);
   htemp__1__1__2__1->GetZaxis()->SetLabelSize(0.06);
   htemp__1__1__2__1->GetZaxis()->SetTitleSize(0.07);
   htemp__1__1__2__1->GetZaxis()->SetTitleFont(42);
   htemp__1__1__2__1->Draw("");
   
   TGraph *graph1 = new TGraph(40);
   graph1->SetName("Graph");
   graph1->SetTitle("Graph");
   graph1->SetFillColor(1);
   graph1->SetMarkerColor(2);
   graph1->SetMarkerStyle(21);
   graph1->SetPoint(0,10,20.8);
   graph1->SetPoint(1,9.75,20.06);
   graph1->SetPoint(2,9.5,19.92);
   graph1->SetPoint(3,9.25,19.29);
   graph1->SetPoint(4,9,19.32);
   graph1->SetPoint(5,8.75,18.47);
   graph1->SetPoint(6,8.5,18.39);
   graph1->SetPoint(7,8.25,18.56);
   graph1->SetPoint(8,8,18.59);
   graph1->SetPoint(9,7.75,17.36);
   graph1->SetPoint(10,7.5,18.04);
   graph1->SetPoint(11,7.25,17.03);
   graph1->SetPoint(12,7,17.86);
   graph1->SetPoint(13,6.75,18.15);
   graph1->SetPoint(14,6.5,17.77);
   graph1->SetPoint(15,6.25,18.06);
   graph1->SetPoint(16,6,17.66);
   graph1->SetPoint(17,5.75,18.09);
   graph1->SetPoint(18,5.5,18.51);
   graph1->SetPoint(19,5.25,17.32);
   graph1->SetPoint(20,5,17.77);
   graph1->SetPoint(21,4.75,16.61);
   graph1->SetPoint(22,4.5,16.52);
   graph1->SetPoint(23,4.25,16.61);
   graph1->SetPoint(24,4,17.67);
   graph1->SetPoint(25,3.75,17.53);
   graph1->SetPoint(26,3.5,17.34);
   graph1->SetPoint(27,3.25,18.17);
   graph1->SetPoint(28,3,17.37);
   graph1->SetPoint(29,2.740156,16.97036);
   graph1->SetPoint(30,2.5,18.98);
   graph1->SetPoint(31,2.25,19.05);
   graph1->SetPoint(32,1.999793,18.42105);
   graph1->SetPoint(33,1.75,18.86);
   graph1->SetPoint(34,1.5,18.73);
   graph1->SetPoint(35,1.25,19.09);
   graph1->SetPoint(36,1,17.98);
   graph1->SetPoint(37,0.75,16.95);
   graph1->SetPoint(38,0.5,8.47);
   graph1->SetPoint(39,0.25,2.1);
   
   TH1F *Graph_Graph_Graph_Graph_Graph1131 = new TH1F("Graph_Graph_Graph_Graph_Graph1131","Graph",100,0,10.975);
   Graph_Graph_Graph_Graph_Graph1131->SetMinimum(0);
   Graph_Graph_Graph_Graph_Graph1131->SetMaximum(25);
   Graph_Graph_Graph_Graph_Graph1131->SetDirectory(0);
   Graph_Graph_Graph_Graph_Graph1131->SetStats(0);
   Graph_Graph_Graph_Graph_Graph1131->SetLineColor(4);
   Graph_Graph_Graph_Graph_Graph1131->SetLineWidth(2);
   Graph_Graph_Graph_Graph_Graph1131->GetXaxis()->SetNdivisions(506);
   Graph_Graph_Graph_Graph_Graph1131->GetXaxis()->SetLabelFont(42);
   Graph_Graph_Graph_Graph_Graph1131->GetXaxis()->SetLabelSize(0.06);
   Graph_Graph_Graph_Graph_Graph1131->GetXaxis()->SetTitleSize(0.07);
   Graph_Graph_Graph_Graph_Graph1131->GetXaxis()->SetTitleFont(42);
   Graph_Graph_Graph_Graph_Graph1131->GetYaxis()->SetNdivisions(506);
   Graph_Graph_Graph_Graph_Graph1131->GetYaxis()->SetLabelFont(42);
   Graph_Graph_Graph_Graph_Graph1131->GetYaxis()->SetLabelSize(0.06);
   Graph_Graph_Graph_Graph_Graph1131->GetYaxis()->SetTitleSize(0.07);
   Graph_Graph_Graph_Graph_Graph1131->GetYaxis()->SetTitleOffset(1.05);
   Graph_Graph_Graph_Graph_Graph1131->GetYaxis()->SetTitleFont(42);
   Graph_Graph_Graph_Graph_Graph1131->GetZaxis()->SetLabelFont(42);
   Graph_Graph_Graph_Graph_Graph1131->GetZaxis()->SetLabelSize(0.06);
   Graph_Graph_Graph_Graph_Graph1131->GetZaxis()->SetTitleSize(0.07);
   Graph_Graph_Graph_Graph_Graph1131->GetZaxis()->SetTitleFont(42);
   graph1->SetHistogram(Graph_Graph_Graph_Graph_Graph1131);
   
   graph1->Draw("p");
   
   graph2 = new TGraph(40);
   graph2->SetName("Graph");
   graph2->SetTitle("Graph");
   graph2->SetFillColor(1);
   graph2->SetMarkerColor(4);
   graph2->SetMarkerStyle(23);
   graph2->SetPoint(0,9.995576,1.556709);
   graph2->SetPoint(1,9.74155,1.232394);
   graph2->SetPoint(2,9.49962,1.093402);
   graph2->SetPoint(3,9.245593,1.139733);
   graph2->SetPoint(4,8.991567,1.093402);
   graph2->SetPoint(5,8.749637,1.000741);
   graph2->SetPoint(6,8.495611,1.047072);
   graph2->SetPoint(7,8.241584,1.232394);
   graph2->SetPoint(8,7.999654,1.139733);
   graph2->SetPoint(9,7.745628,0.90808);
   graph2->SetPoint(10,7.491602,1.000741);
   graph2->SetPoint(11,7.249672,0.90808);
   graph2->SetPoint(12,6.995645,1.047072);
   graph2->SetPoint(13,6.741619,0.8617494);
   graph2->SetPoint(14,6.499689,0.8617494);
   graph2->SetPoint(15,6.245663,0.9544106);
   graph2->SetPoint(16,5.991636,0.6764269);
   graph2->SetPoint(17,5.749706,0.8617494);
   graph2->SetPoint(18,5.49568,0.90808);
   graph2->SetPoint(19,5.241653,0.6764269);
   graph2->SetPoint(20,4.999724,0.7690882);
   graph2->SetPoint(21,4.745697,0.7227575);
   graph2->SetPoint(22,4.491671,0.5374351);
   graph2->SetPoint(23,4.249741,0.8154188);
   graph2->SetPoint(24,3.995714,0.7690882);
   graph2->SetPoint(25,3.741688,0.8154188);
   graph2->SetPoint(26,3.499758,0.7690882);
   graph2->SetPoint(27,3.245732,0.6764269);
   graph2->SetPoint(28,2.991705,0.7690882);
   graph2->SetPoint(29,2.749775,0.7227575);
   graph2->SetPoint(30,2.495749,0.8617494);
   graph2->SetPoint(31,2.241723,0.7227575);
   graph2->SetPoint(32,1.999793,0.5837657);
   graph2->SetPoint(33,1.745766,0.5837657);
   graph2->SetPoint(34,1.49174,0.4911045);
   graph2->SetPoint(35,1.24981,0.3521126);
   graph2->SetPoint(36,0.9957836,0.2131208);
   graph2->SetPoint(37,0.7417572,0.2131208);
   graph2->SetPoint(38,0.4998273,0.1204595);
   graph2->SetPoint(39,0.2458009,0.02779832);
   
   graph2->SetHistogram(Graph_Graph_Graph_Graph_Graph1131);
   
   graph2->Draw("p");
   

TGraph *graph3 = new TGraph(37);
   graph3->SetName("Graph");
   graph3->SetTitle("Graph");
   graph3->SetFillColor(0);
   graph3->SetMarkerColor(1);
   graph3->SetMarkerStyle(21);


double value_orig2[37][2]={
{0.50, 13.85},{0.74, 14.84},{0.98, 14.30},{1.24, 14.33},
{1.49, 13.91},{1.74, 13.97},{2.01, 13.37},{2.26, 13.58},
{2.50, 13.19},{2.75, 12.53},{3.00, 12.38},{3.24, 13.31},
{3.50, 12.71},{3.75, 12.41},{3.99, 12.32},{4.49, 11.90},
{4.74, 12.53},{5.00, 12.41},{5.26, 12.05},{5.50, 11.78},
{5.75, 11.66},{6.01, 11.51},{6.25, 11.27},{6.49, 11.12},
{6.75, 11.03},{7.00, 10.82},{7.25, 10.85},{7.50, 10.91},
{7.75, 11.03},{7.99, 11.12},{8.25, 11.33},{8.50, 11.45},
{8.75, 11.93},{9.00, 12.47},{9.25, 12.90},{9.50, 13.20},
{10.00, 13.65}};

for(int i =0; i<37 ;i++)
   graph3->SetPoint(i,value_orig2[i][0],value_orig2[i][1]);
	
   graph3->SetHistogram(Graph_Graph_Graph_Graph_Graph1131);
	graph3->Draw("p");

   TGraph *graph4 = new TGraph(40);
   graph4->SetName("Graph");
   graph4->SetTitle("Graph");
   graph4->SetMarkerColor(3);
   graph4->SetMarkerStyle(21);
   graph4->SetPoint(0,10,22.55);
   graph4->SetPoint(1,9.75,21.88);
   graph4->SetPoint(2,9.5,21.92);
   graph4->SetPoint(3,9.25,21.01);
   graph4->SetPoint(4,9,21.05);
   graph4->SetPoint(5,8.75,20.17);
   graph4->SetPoint(6,8.5,20.29);
   graph4->SetPoint(7,8.25,20.13);
   graph4->SetPoint(8,8,20.4);
   graph4->SetPoint(9,7.75,18.91);
   graph4->SetPoint(10,7.5,20.05);
   graph4->SetPoint(11,7.25,18.83);
   graph4->SetPoint(12,7,19.62);
   graph4->SetPoint(13,6.75,19.7);
   graph4->SetPoint(14,6.5,19.75);
   graph4->SetPoint(15,6.25,19.97);
   graph4->SetPoint(16,6,19.61);
   graph4->SetPoint(17,5.75,20.13);
   graph4->SetPoint(18,5.5,20.29);
   graph4->SetPoint(19,5.25,19.41);
   graph4->SetPoint(20,5,19.74);
   graph4->SetPoint(21,4.75,19.34);
   graph4->SetPoint(22,4.5,19);
   graph4->SetPoint(23,4.25,18.4);
   graph4->SetPoint(24,4,19.67);
   graph4->SetPoint(25,3.75,19.45);
   graph4->SetPoint(26,3.5,19.15);
   graph4->SetPoint(27,3.25,20.19);
   graph4->SetPoint(28,3,19.93);
   graph4->SetPoint(29,2.75,18.6);
   graph4->SetPoint(30,2.5,20.52);
   graph4->SetPoint(31,2.25,20.95);
   graph4->SetPoint(32,2,19.96);
   graph4->SetPoint(33,1.75,20.57);
   graph4->SetPoint(34,1.5,20.63);
   graph4->SetPoint(35,1.25,21.79);
   graph4->SetPoint(36,1,20.59);
   graph4->SetPoint(37,0.75,20.33);
   graph4->SetPoint(38,0.5,20.2);
   graph4->SetPoint(39,0.25,2.11);
   
   graph4->SetHistogram(Graph_Graph_Graph_Graph_Graph1131);
   graph4->Draw("p");



   TLegend *leg = new TLegend(0.5805627,0.3098592,0.8994032,0.528169,NULL,"brNDC");
   leg->SetBorderSize(1);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(10);
   leg->SetFillStyle(1001);
   leg->AddEntry(graph3,"MCNP one scintillator","p");
   leg->AddEntry(graph1,"Geant4 one scintillator","p");
   leg->AddEntry(graph4,"Geant4 linear energy deposition","p");
   leg->AddEntry(graph2,"Geant4 two scintillators","p");
   leg->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
