

//#include <iostream>
//#define NPoints 1280



void plot(const char* FileName = "", bool writeOnFile = false){


	gROOT->Reset();
	gROOT->SetBatch(kTRUE);

  int tempfEvent;
	double tempfX;
	double tempfY;
  int Hatt=0;

  double xGun;
  double yGun;
  double xDet;
  double yDet;
  double xRes;
  double yRes;

	int association[2][1024];
	int PixID = 0;
	for(int i = 0; i < 32; i++){
		for(int j = 0; j < 32; j++){
			association[0][PixID]=i; association[1][PixID]=j; PixID++;
		}
	}

	TFile *output_f= new TFile(Form("analysis_%s",FileName),"RECREATE");
	TFile *input_f= new TFile(FileName,"READ");

	TTree *T = (TTree*)input_f->Get("Photons");
	T->SetBranchAddress("fEvent",&tempfEvent);
	T->SetBranchAddress("fX",&tempfX);
	T->SetBranchAddress("fY",&tempfY);
	TTree *T1 = (TTree*)input_f->Get("Hits");
	T1->SetBranchAddress("fEvent",&tempfEvent);
	T1->SetBranchAddress("fX",&tempfX);
	T1->SetBranchAddress("fY",&tempfY);
	T1->SetBranchAddress("Hpix",&Hatt);
	TTree *T2 = (TTree*)input_f->Get("Scoring");
  T2->SetBranchAddress("fEvent",&tempfEvent);
	T2->SetBranchAddress("xGun",&xGun);
	T2->SetBranchAddress("yGun",&yGun);

  output_f->cd();
  TTree *Tout = new TTree("Tout","Residuals");
  Tout->Branch("fEvent",&tempfEvent);
  Tout->Branch("xGun",&xGun);
  Tout->Branch("yGun",&yGun);
  Tout->Branch("xDet",&xDet);
  Tout->Branch("yDet",&yDet);
  Tout->Branch("xRes",&xRes);
  Tout->Branch("yRes",&yRes);


  vector<int> g1;
  int T2entries = T2->GetEntries();

  for (int k = 0; k < T2entries; k++){
    T2->GetEntry(k);
    g1.push_back(tempfEvent);
    //cout<<tempfEvent<<endl;
  }
//cout<<endl;

  Int_t u=0;
  Int_t u1=0;
  Int_t g1_size=g1.size();


  for(int pos=0; pos<g1_size; pos++){

    //cout<<"event "<<g1[pos]<<endl;
    //cout<<"u "<<u<<endl;
    //cout<<"u1 "<<u1<<endl;

  	TH2I* Generated=new TH2I(Form("Generated_%i",g1[pos]), Form("Generated_%i;x(mm);y(mm)",g1[pos]),32,-1.155,1.155,32,-1.254,1.254);
  	TH2I* Detected=new TH2I(Form("Detected_%i",g1[pos]), Form("Detected_%i;x(mm);y(mm)",g1[pos]),32,-1.155,1.155,32,-1.254,1.254);
  	TH2I* GeneratedBin=new TH2I(Form("GeneratedBin_%i",g1[pos]), Form("GeneratedBin_%i;x(mm);y(mm)",g1[pos]),32,-1.155,1.155,32,-1.254,1.254);
  	TH2I* DetectedBin=new TH2I(Form("DetectedBin_%i",g1[pos]), Form("DetectedBin_%i;x(mm);y(mm)",g1[pos]),32,-1.155,1.155,32,-1.254,1.254);

    //fill Generated
  	int nentries=T->GetEntries();//entrate del tree di input
  	int Ph[32][32]={0};

  	for (;u<nentries; u++) {
        T->GetEntry(u);
        //cout<<"tempevent "<<tempfEvent<<endl;
        if(tempfEvent>g1[pos]){u-=2; break;}
  			if(tempfEvent!=g1[pos]){continue;}
  			for(int i=0;i<32;i++){
  				for(int j=0;j<32;j++){
  					if(tempfEvent==g1[pos] && tempfX>(-1.120+0.070*i) && tempfX<=(-1.120+0.070*i+0.070)  && tempfY>(-1.216+0.076*j) && tempfY<=(-1.216+0.076*j+0.076)){
              Ph[i][j]++;
  					}
  				}
  			}
  		}

    nentries=T1->GetEntries();
  	int HitMap[32][32]={0};
   	for (;u1<nentries; u1++) {
        T1->GetEntry(u1);
      //  cout<<"tempevent "<<tempfEvent<<">"<<g1[pos]<<endl;
        if(tempfEvent>g1[pos]){u1-=2;break;}
  			if(tempfEvent!=g1[pos]){continue;}
  			if(tempfEvent==g1[pos]){
              HitMap[association[0][Hatt]][association[1][Hatt]]++;
  					}
  		}


  	for(int i=0;i<32;i++){
    	for(int j=0;j<32;j++){
  			Generated->SetBinContent(i+1, j+1, Ph[i][j]);
  			Detected->SetBinContent(i+1, j+1, HitMap[i][j]);
  			if(Ph[i][j]>0){GeneratedBin->SetBinContent(i+1, j+1, 1);}
  			if(HitMap[i][j]>0){DetectedBin->SetBinContent(i+1, j+1, 1);}
  		}
  	}
    Generated->ResetStats();
  	Detected->ResetStats();
  	GeneratedBin->ResetStats();
  	DetectedBin->ResetStats();
  	TH1D * HitX = DetectedBin->ProjectionX();
    TH1D * HitY = DetectedBin->ProjectionY();
  	TF1 *f1 = new TF1(Form("f1_%i",g1[pos]),"[0]*exp(-0.5*((x-[1])/[2])^2)",-1.155,1.155);
  	TF1 *f2 = new TF1(Form("f2_%i",g1[pos]),"[0]*exp(-0.5*((x-[1])/[2])^2)",-1.254,1.254);
    f1->SetParameter(0,10);
    f2->SetParameter(0,10);
    f1->SetParameter(1,0);
    f2->SetParameter(1,0);
    f1->SetParameter(2,0.3);
    f2->SetParameter(2,0.3);
    f1->SetParLimits(0,0.,1000);
  	f2->SetParLimits(0,0.,1000);
    f1->SetParLimits(1,-1.155,1.155);
  	f2->SetParLimits(1,-1.254,1.254);
    f1->SetParLimits(2,0.,0.5);
  	f2->SetParLimits(2,0.,0.5);
  	HitX-> Fit(Form("f1_%i",g1[pos]),"LBQ");
  	HitY-> Fit(Form("f2_%i",g1[pos]),"LBQ");

    xDet=f1->GetParameter(1);
    yDet=f2->GetParameter(1);
    input_f->cd();

    int j=0;
    while(true){
      T2->GetEntry(j);
      if(tempfEvent==g1[pos]){break;}
      j++;
    }
    //cout<<xGun<<" "<<xDet<<endl;
    xRes=xGun-xDet;
    yRes=yGun-yDet;
    Tout->Fill();


  	if(writeOnFile){
  	  output_f->cd();
  		Generated->Write(Form("Generated_%i",g1[pos]));
  	  Detected->Write(Form("Detected_%i",g1[pos]));
  		GeneratedBin->Write(Form("GeneratedBin_%i",g1[pos]));
  	  DetectedBin->Write(Form("DetectedBin_%i",g1[pos]));
  		HitX->Write(Form("HitX_%i",g1[pos]));
    	HitY->Write(Form("HitY_%i",g1[pos]));
  	}
  }

  output_f->cd();
  Tout->Write();
	input_f->Close();
	output_f->Close();
  gROOT->SetBatch(kFALSE);
  return;
}
