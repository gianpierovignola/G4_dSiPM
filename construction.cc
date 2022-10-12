#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{
    nCols = 32;
    nRows = 32;

    fMessenger = new G4GenericMessenger(this, "/detector/", "Detector Construction");

    fMessenger->DeclareProperty("nCols", nCols, "Number of cols");
    fMessenger->DeclareProperty("nRows", nRows, "Number of rows");

    //per Silicone
    nistMan = G4NistManager::Instance();
    nistMan->SetVerbose(2);
    //



    DefineMaterials();


}

MyDetectorConstruction::~MyDetectorConstruction()
{}

void MyDetectorConstruction::DefineMaterials()
{
    G4NistManager *nist = G4NistManager::Instance();

    C = nist->FindOrBuildElement("C");
    SiO2 = new G4Material("SiO2", 2.201*g/cm3, 2);
    Aerogel = new G4Material("Aerogel", 0.200*g/cm3, 3);
    worldMat = nist->FindOrBuildMaterial("G4_AIR");
    H2O = new G4Material("H2O", 1.000*g/cm3, 2);

    SiO2->AddElement(nist->FindOrBuildElement("Si"), 1);
    SiO2->AddElement(nist->FindOrBuildElement("O"), 2);

    H2O->AddElement(nist->FindOrBuildElement("H"), 2);
    H2O->AddElement(nist->FindOrBuildElement("O"), 1);

    Aerogel->AddMaterial(SiO2, 62.5*perCent);
    Aerogel->AddMaterial(H2O, 37.4*perCent);
    Aerogel->AddElement(C, 0.1*perCent);

    G4double energy[2] = {1.239841939*eV/0.2, 1.239841939*eV/0.9};
    G4double rindexAerogel[2] = {1.1, 1.1};
    G4double rindexWorld[2] = {1.0, 1.0};
    G4double rindexNaI[2] = {1.78, 1.78}; // TO EXTEND

    G4MaterialPropertiesTable *mptAerogel = new G4MaterialPropertiesTable();
    mptAerogel->AddProperty("RINDEX", energy, rindexAerogel, 2);

    Aerogel->SetMaterialPropertiesTable(mptAerogel);

    G4MaterialPropertiesTable *mptWorld = new G4MaterialPropertiesTable();
    mptWorld->AddProperty("RINDEX", energy, rindexWorld, 2);

    worldMat->SetMaterialPropertiesTable(mptWorld);

    //physScintillator NaI
    Na = nist->FindOrBuildElement("Na");
    I = nist->FindOrBuildElement("I");
    NaI = new G4Material("NaI", 3.67*g/cm3, 2);
    NaI->AddElement(Na, 1);
    NaI->AddElement(I, 1);

    G4double fraction[2] = {1.0, 1.0}; // TO EXTEND

    G4MaterialPropertiesTable *mptNaI = new G4MaterialPropertiesTable();
    mptNaI->AddProperty("RINDEX", energy, rindexNaI, 2);
    mptNaI->AddProperty("FASTCOMPONENT", energy, fraction, 2);
    mptNaI->AddConstProperty("SCINTILLATIONYIELD",38./keV);
    mptNaI->AddConstProperty("RESOLUTIONSCALE",1.0);
    mptNaI->AddConstProperty("FASTTIMECONSTANT", 250.*ns);
    mptNaI->AddConstProperty("YIELDRATIO",1.);
    NaI->SetMaterialPropertiesTable(mptNaI);

    // LYSO
    LYSO = MyMaterials::LYSO();

    //Silicone
    G4double density;
    std::vector<G4int> natoms;
    std::vector<G4String> elements;


    elements.push_back("C");     natoms.push_back(2);
    elements.push_back("H");     natoms.push_back(6);

    density = 1.060*g/cm3;

    Silicone = nistMan->
            ConstructNewMaterial("Silicone", elements, natoms, density);

    elements.clear();
    natoms.clear();

    /*
    const G4int nEntries = 50;

    G4double PhotonEnergy[nEntries] =
    {2.00*eV,2.03*eV,2.06*eV,2.09*eV,2.12*eV,
     2.15*eV,2.18*eV,2.21*eV,2.24*eV,2.27*eV,
     2.30*eV,2.33*eV,2.36*eV,2.39*eV,2.42*eV,
     2.45*eV,2.48*eV,2.51*eV,2.54*eV,2.57*eV,
     2.60*eV,2.63*eV,2.66*eV,2.69*eV,2.72*eV,
     2.75*eV,2.78*eV,2.81*eV,2.84*eV,2.87*eV,
     2.90*eV,2.93*eV,2.96*eV,2.99*eV,3.02*eV,
     3.05*eV,3.08*eV,3.11*eV,3.14*eV,3.17*eV,
     3.20*eV,3.23*eV,3.26*eV,3.29*eV,3.32*eV,
     3.35*eV,3.38*eV,3.41*eV,3.44*eV,3.47*eV};

     G4double AbsClad[nEntries] =
    {20.0*m,20.0*m,20.0*m,20.0*m,20.0*m,20.0*m,20.0*m,20.0*m,20.0*m,20.0*m,
     20.0*m,20.0*m,20.0*m,20.0*m,20.0*m,20.0*m,20.0*m,20.0*m,20.0*m,20.0*m,
     20.0*m,20.0*m,20.0*m,20.0*m,20.0*m,20.0*m,20.0*m,20.0*m,20.0*m,20.0*m,
     20.0*m,20.0*m,20.0*m,20.0*m,20.0*m,20.0*m,20.0*m,20.0*m,20.0*m,20.0*m,
     20.0*m,20.0*m,20.0*m,20.0*m,20.0*m,20.0*m,20.0*m,20.0*m,20.0*m,20.0*m};


     G4double RefractiveIndexSilicone[nEntries] =
     { 1.46, 1.46, 1.46, 1.46, 1.46, 1.46, 1.46, 1.46, 1.46, 1.46,
     1.46, 1.46, 1.46, 1.46, 1.46, 1.46, 1.46, 1.46, 1.46, 1.46,
     1.46, 1.46, 1.46, 1.46, 1.46, 1.46, 1.46, 1.46, 1.46, 1.46,
     1.46, 1.46, 1.46, 1.46, 1.46, 1.46, 1.46, 1.46, 1.46, 1.46,
     1.46, 1.46, 1.46, 1.46, 1.46, 1.46, 1.46, 1.46, 1.46, 1.46};

    // Add entries into properties table
    G4MaterialPropertiesTable* MPTSilicone = new G4MaterialPropertiesTable();
    MPTSilicone->AddProperty("RINDEX",PhotonEnergy,RefractiveIndexSilicone,nEntries);
    MPTSilicone->AddProperty("ABSLENGTH",PhotonEnergy,AbsClad,nEntries);
    */
    G4double rindexSilicone[2] = {1.46, 1.46};
    G4MaterialPropertiesTable* MPTSilicone = new G4MaterialPropertiesTable();
    MPTSilicone->AddProperty("RINDEX", energy, rindexSilicone, 2);
    //MPTSilicone->AddProperty("ABSLENGTH",PhotonEnergy,AbsClad,nEntries);

    Silicone->SetMaterialPropertiesTable(MPTSilicone);

    // BGO
    G4int NUMENTRIES = 3;
  	G4double BSO_Energy[NUMENTRIES] = {2.0*eV, 2.87*eV, 2.9*eV};
  	BGO = new G4Material("BGO", 7.13*g/cm3, 3);
    Bi = nist->FindOrBuildElement("Bi");
    Ge = nist->FindOrBuildElement("Ge");
    O = nist->FindOrBuildElement("O");
  	BGO->AddElement(Bi, 4);
  	BGO->AddElement(Ge, 3);
  	BGO->AddElement(O, 12);
  	G4double RIndexBGO[NUMENTRIES]={ 2.15, 2.15, 2.15};
  	G4double Absorption1[NUMENTRIES]={24.*cm, 24.*cm, 24.*cm}; //http://www.sciencedirect.com/science/article/pii/0167508784900930
  	G4double ScintilFast[NUMENTRIES]={0.00, 0.00, 1.00}; //I don't know what this is or if it is right
  	G4MaterialPropertiesTable* MPT_BGO = new G4MaterialPropertiesTable();
  	MPT_BGO->AddProperty("RINDEX",BSO_Energy,RIndexBGO,NUMENTRIES);
  	MPT_BGO->AddProperty("ABSLENGTH",BSO_Energy,Absorption1,NUMENTRIES);
  	MPT_BGO->AddProperty("FASTCOMPONENT",BSO_Energy,ScintilFast,NUMENTRIES);
  	// 	MPT_BGO->AddProperty("SLOWCOMPONENT",BSO_Energy, ScintilFast,NUMENTRIES);
  	MPT_BGO->AddConstProperty("SCINTILLATIONYIELD",2000./MeV);
  	MPT_BGO->AddConstProperty("RESOLUTIONSCALE",1.0); //creates a statistcal flucution, higher values broaden it; 0 = no fluctuation
  	MPT_BGO->AddConstProperty("FASTTIMECONSTANT", 100.*ns); //Is this right???
    // 	MPT_BGO->AddConstProperty("SLOWTIMECONSTANT", 100.*ns); // because the yield ratio is set at 1.0, there is no slow scintillation
    // 	MPT_BGO->AddConstProperty("YIELDRATIO",1.0);  // all of the scintillation is fast (fast component)
  	BGO->SetMaterialPropertiesTable(MPT_BGO);
  	//BGO does not have a Birks Coefficient because it is not a plastic scintillator (and thus does not have a non-linear response)


    //mirrorSurface
    mirrorSurface = new G4OpticalSurface("mirrorSurface");
    G4double reflectivity[2] = {0.1, 0.1};

    G4MaterialPropertiesTable *mptMirror = new G4MaterialPropertiesTable();
    mptMirror->AddProperty("REFLECTIVITY", energy, reflectivity, 2);
    mirrorSurface->SetMaterialPropertiesTable(mptMirror);
    mirrorSurface->SetType(dielectric_metal);
    mirrorSurface->SetFinish(ground);
    mirrorSurface->SetModel(unified);


    worldMat->SetMaterialPropertiesTable(mptWorld);
}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
    G4double xWorld = 0.5*cm;
    G4double yWorld = 0.5*cm;
    G4double zWorld = 2*mm;

    G4Colour brown(0.7, 0.4, 0.1);
    G4Colour blue(0., 0., 1.);
    G4VisAttributes* brownVisAttributes = new G4VisAttributes(brown);
    G4VisAttributes* blueVisAttributes = new G4VisAttributes(blue);

    solidWorld = new G4Box("solidWorld", xWorld, yWorld, zWorld);

    logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");

    physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);

    solidScintillator = new G4Box("solidScintillator", 0.5*cm, 0.5*cm, 0.5*mm);

    logicScintillator = new G4LogicalVolume(solidScintillator, Silicone, "logicalScintillator");

    logicScintillator->SetVisAttributes(blueVisAttributes);

    G4LogicalSkinSurface *skin = new G4LogicalSkinSurface("skin", logicWorld, mirrorSurface);

    fScoringVolume = logicScintillator;

    physScintillator = new G4PVPlacement(0, G4ThreeVector(0., 0., 1.4*mm), logicScintillator, "physScintillator", logicWorld, false, 0, true);

    solidDetector = new G4Box("solidDetector", xWorld/nRows, xWorld/nCols, 0.05*mm);

    logicDetector = new G4LogicalVolume(solidDetector, worldMat, "logicDetector");

    logicDetector->SetVisAttributes(brownVisAttributes);

    for(G4int i = 0; i < nRows; i++)
    {
        for(G4int j = 0; j < nCols; j++)
        {
            physDetector = new G4PVPlacement(0, G4ThreeVector(-0.5*mm+(i+0.5)*mm/nRows, -0.5*mm+(j+0.5)*mm/nCols, 1.95*mm), logicDetector, "physDetector", logicWorld, false, j+i*nCols, true);
        }
    }

    return physWorld;
}

void MyDetectorConstruction::ConstructSDandField()
{
    MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");

    logicDetector->SetSensitiveDetector(sensDet);
}
