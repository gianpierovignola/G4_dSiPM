//#include <iostream>
//#define NPoints 1280



void plot(const char* FileName = "", int ev = 1){

	float pixposx[33]={-1.15,-1.06,-1,-0.9,-0.84,
		-0.76,-0.7,-0.63,-0.56,-0.5,-0.4,
		-0.35,-0.3,-0.2,-0.14,-0.08,0, 0.08,
		0.14,0.2,0.3,0.35,0.4,0.5,0.56,0.63,
		0.7, 0.76,0.84,0.9,1,1.06,1.15};

		float pixposy[33]={
			-1.25,-1.15,-1.05,-1, -0.9,
			-0.85,-0.75, -0.7,-0.6, -0.54,
			-0.45, -0.4, -0.3, -0.23, -0.15,
			-0.08, 0, 0.08, 0.15, 0.23, 0.3,
			0.4, 0.45, 0.54, 0.6, 0.7, 0.75, 0.85,
			0.9, 1, 1.05, 1.15, 1.25};

	gROOT->Reset();
	gROOT->SetBatch(kTRUE);

  int tempfEvent;
	double tempfX;
	double tempfY;

	TFile *output_f= new TFile(Form("analysis_EV%i_%s",ev,FileName),"RECREATE");
	TFile *input_f= new TFile(FileName,"READ");

	TH2I* Generated=new TH2I("Generated", "Generated;x(pix);y(pix)",32,-0.5,31.5,32,-0.5,31.5);
	TH2I* Detected=new TH2I("Detected", "Detected;x(pix);y(pix)",32,-0.5,31.5,32,-0.5,31.5);
	TH2I* GeneratedBin=new TH2I("GeneratedBin", "GeneratedBin;x(pix);y(pix)",32,-0.5,31.5,32,-0.5,31.5);
	TH2I* DetectedBin=new TH2I("DetectedBin", "DetectedBin;x(pix);y(pix)",32,-0.5,31.5,32,-0.5,31.5);

  TTree *T = (TTree*)input_f->Get("Photons");
	T->Draw("fX:fY>>Generated","fEvent==1","");
  T->Draw("fX>>Generatedx","fEvent==1","");
	T->Draw("fY>>Generatedy","fEvent==1","");

	T->SetBranchAddress("fEvent",&tempfEvent);
	T->SetBranchAddress("fX",&tempfX);
	T->SetBranchAddress("fY",&tempfY);


	TTree *T1 = (TTree*)input_f->Get("Hits");
	T1->Draw("fX:fY>>Detected","fEvent==1","");
  T1->Draw("fX>>Detectedx","fEvent==1","");
	T1->Draw("fY>>Detectedy","fEvent==1","");

	T1->SetBranchAddress("fEvent",&tempfEvent);
	T1->SetBranchAddress("fX",&tempfX);
	T1->SetBranchAddress("fY",&tempfY);


	int nentries=T->GetEntries();//entrate del tree di input
	int Ph[32][32]={0};
	int HitMap[32][32]={0};

	for (Int_t u=0;u<nentries; u++) {
      T->GetEntry(u);
			if(tempfEvent>ev){break;}
			if(tempfEvent!=ev){continue;}
			//cout<<"trovo "<<tempfX<<" "<<tempfY<<endl;
			for(int i=0;i<32;i++){
				for(int j=0;j<32;j++){

					if(tempfEvent==ev && tempfX>(-1.120+0.070*i) && tempfX<=(-1.120+0.070*i+0.070)  && tempfY>(-1.216+0.076*j) && tempfY<=(-1.216+0.076*j+0.076)){
            //cout<<"incremento "<<i<<" "<<j<<endl;
						Ph[i][j]++;
					}
				}
			}
		}

  nentries=T1->GetEntries();
 	for (Int_t u=0;u<nentries; u++) {
      T1->GetEntry(u);
			if(tempfEvent>ev){break;}
			if(tempfEvent!=ev){continue;}
			for(int i=0;i<32;i++){
				for(int j=0;j<32;j++){
					if(tempfEvent==ev && tempfX>pixposx[i] && tempfX<=pixposx[i+1] && tempfY>pixposy[j] && tempfY<=pixposy[j+1]){
            HitMap[i][j]++;
					}
				}
			}
		}

	for(int i=0;i<32;i++){
  	for(int j=0;j<32;j++){
			//cout<<i<<" "<<j<<" "<<HitMap[i][j]<<endl;
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
	TF1 *f1 = new TF1("f1","gaus",0,32);
	f1->SetParLimits(1,0,32);
	HitX-> Fit("f1");
	HitY-> Fit("f1");


  output_f->cd();
	Generated->Write("Generated");
  Detected->Write("Detected");
	GeneratedBin->Write("GeneratedBin");
  DetectedBin->Write("DetectedBin");
	HitX->Write("HitX");
  HitY->Write("HitY");
	input_f->Close();
	output_f->Close();
  gROOT->SetBatch(kFALSE);
  return;
}
