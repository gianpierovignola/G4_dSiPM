#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{
  fMessenger = new G4GenericMessenger(this, "/detector/", "Detector Construction");

  fMessenger->DeclareProperty("nx", nx, "Number of cols");
  fMessenger->DeclareProperty("ny", ny, "Number of rows");
  fMessenger->DeclareProperty("xgap", xgap, "xgap um");
  fMessenger->DeclareProperty("ygap", ygap, "ygap um");
  fMessenger->DeclareProperty("xpitch", xpitch, "xpitch um");
  fMessenger->DeclareProperty("ypitch", ypitch, "ypitch um");
  fMessenger->DeclareProperty("radthick", radthick, "radthick um");
  fMessenger->DeclareProperty("DUTthick", DUTthick, "DUTthick um");

  nx = 3;
  ny = 3;
  xgap = 200;
  ygap = 200;
  xpitch = 1000;
  ypitch = 1000;
  radthick = 1000;
  DUTthick = 300;

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

    //list of used atoms
    H = nist->FindOrBuildElement("H");
    C = nist->FindOrBuildElement("C");
    O = nist->FindOrBuildElement("O");
    N = nist->FindOrBuildElement("N");
    Na = nist->FindOrBuildElement("Na");
    I = nist->FindOrBuildElement("I");
    Bi = nist->FindOrBuildElement("Bi");
    Si = nist->FindOrBuildElement("Si");
    Ge = nist->FindOrBuildElement("Ge");
    Lu = nist->FindOrBuildElement("Lu");

    //Air
    Air = new G4Material ("Air", 1.29 * mg/cm3, 2);
    Air->AddElement (N, 70.*perCent);
    Air->AddElement (O, 30.*perCent);

    const G4int nEntriesAir = 34;
    G4double PhotonEnergyAir[nEntriesAir] = {
      0.0001 * eV, 1.00 * eV,  2.034 * eV, 2.068 * eV, 2.103 * eV, 2.139 * eV, 2.177 * eV, 2.216 * eV, 2.256 * eV, 2.298 * eV, 2.341 * eV, 2.386 * eV, 2.433 * eV, 2.481 * eV, 2.532 * eV, 2.585 * eV, 2.640 * eV, 2.697 * eV, 2.757 * eV, 2.820 * eV, 2.885 * eV, 2.954 * eV, 3.026 * eV, 3.102 * eV, 3.181 * eV, 3.265 * eV, 3.353 * eV, 3.446 * eV, 3.545 * eV, 3.649 * eV, 3.760 * eV, 3.877 * eV, 4.002 * eV, 4.136 * eV
    };
    G4double RefractiveIndexAir[nEntriesAir] = {
      1.0003, 1.0003, 1.0003, 1.0003, 1.0003, 1.0003, 1.0003, 1.0003,  1.0003, 1.0003, 1.0003, 1.0003, 1.0003, 1.0003, 1.0003,  1.0003, 1.0003, 1.0003, 1.0003, 1.0003, 1.0003, 1.0003,  1.0003, 1.0003, 1.0003, 1.0003, 1.0003, 1.0003, 1.0003,  1.0003, 1.0003, 1.0003, 1.0003, 1.0003
    };
    G4MaterialPropertiesTable *myMPT = new G4MaterialPropertiesTable();
    myMPT->AddProperty ("RINDEX", PhotonEnergyAir, RefractiveIndexAir, nEntriesAir);
    Air->SetMaterialPropertiesTable (myMPT);


    //H2O
    H2O = new G4Material ("H2O", 1.0*g/cm3, 2);
    H2O->AddElement (H, 2);
    H2O->AddElement (O, 1);

    const G4int nEntriesH20 = 33;

    G4double PhotonEnergyH20[nEntriesH20] = {
      0.1 * eV, 2.034 * eV, 2.068 * eV, 2.103 * eV, 2.139 * eV, 2.177 * eV, 2.216 * eV, 2.256 * eV, 2.298 * eV, 2.341 * eV, 2.386 * eV, 2.433 * eV, 2.481 * eV, 2.532 * eV, 2.585 * eV, 2.640 * eV, 2.697 * eV, 2.757 * eV, 2.820 * eV, 2.885 * eV, 2.954 * eV, 3.026 * eV, 3.102 * eV, 3.181 * eV, 3.265 * eV, 3.353 * eV, 3.446 * eV, 3.545 * eV, 3.649 * eV, 3.760 * eV, 3.877 * eV, 4.002 * eV, 4.136 * eV
    };
    G4double RefractiveIndexH20[nEntriesH20] = {
      1.3435, 1.3435, 1.344,  1.3445, 1.345,  1.3455,  1.346,  1.3465, 1.347,  1.3475, 1.348,  1.3485, 1.3492, 1.35,   1.3505, 1.351,  1.3518, 1.3522, 1.3530, 1.3535, 1.354,  1.3545, 1.355,  1.3555, 1.356,  1.3568,  1.3572, 1.358,  1.3585, 1.359,  1.3595,  1.36,   1.3608
    };
    G4double AbsorptionH20[nEntriesH20] = {
      3.448, 3.448 * m,  4.082 * m,  6.329 * m,  9.174 * m, 12.346 * m, 13.889 * m,  15.152 * m, 17.241 * m, 18.868 * m, 20.000 * m, 26.316 * m, 35.714 * m,  45.455 * m, 47.619 * m, 52.632 * m, 52.632 * m, 55.556 * m, 52.632 * m,  52.632 * m, 47.619 * m, 45.455 * m, 41.667 * m, 37.037 * m, 33.333 * m,  30.000 * m, 28.500 * m, 27.000 * m, 24.500 * m, 22.000 * m, 19.500 * m,  17.500 * m, 14.500 * m
    };
    G4double ScintilFastH20[nEntriesH20] = {
      1.00,   1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,  1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,  1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,  1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,  1.00, 1.00, 1.00, 1.00
    };
    G4double ScintilSlowH20[nEntriesH20] = {
      0.01,   0.01, 1.00, 2.00, 3.00, 4.00, 5.00, 6.00,  7.00, 8.00, 9.00, 8.00, 7.00, 6.00, 4.00,  3.00, 2.00, 1.00, 0.01, 1.00, 2.00, 3.00,  4.00, 5.00, 6.00, 7.00, 8.00, 9.00, 8.00,  7.00, 6.00, 5.00, 4.00
    };
    G4MaterialPropertiesTable *myMPTH2O = new G4MaterialPropertiesTable();
    myMPTH2O->AddProperty ("RINDEX",       PhotonEnergyH20, RefractiveIndexH20, nEntriesH20);
    myMPTH2O->AddProperty ("ABSLENGTH",    PhotonEnergyH20, AbsorptionH20,      nEntriesH20);
    myMPTH2O->AddProperty ("FASTCOMPONENT", PhotonEnergyH20, ScintilFastH20,     nEntriesH20);
    myMPTH2O->AddProperty ("SLOWCOMPONENT", PhotonEnergyH20, ScintilSlowH20,     nEntriesH20);
    myMPTH2O->AddConstProperty ("SCINTILLATIONYIELD", 50. / MeV);
    myMPTH2O->AddConstProperty ("RESOLUTIONSCALE", 1.0);
    myMPTH2O->AddConstProperty ("FASTTIMECONSTANT", 1.*ns);
    myMPTH2O->AddConstProperty ("SLOWTIMECONSTANT", 10.*ns);
    myMPTH2O->AddConstProperty ("YIELDRATIO", 0.8);
    H2O->SetMaterialPropertiesTable (myMPTH2O);

    //SiO2
    SiO2 = new G4Material("SiO2", 2.201*g/cm3, 2);
    SiO2->AddElement(nist->FindOrBuildElement("Si"), 1);
    SiO2->AddElement(nist->FindOrBuildElement("O"), 2);

    //Aerogel
    G4double energyAerogel[2] = {1.239841939*eV/0.2, 1.239841939*eV/0.9}; // TO EXTEND
    G4double rindexAerogel[2] = {1.1, 1.1}; // TO EXTEND
    Aerogel = new G4Material("Aerogel", 0.200*g/cm3, 3);
    Aerogel->AddMaterial(SiO2, 62.5*perCent);
    Aerogel->AddMaterial(H2O, 37.4*perCent);
    Aerogel->AddElement(C, 0.1*perCent);
    G4MaterialPropertiesTable *mptAerogel = new G4MaterialPropertiesTable();
    mptAerogel->AddProperty("RINDEX", energyAerogel, rindexAerogel, 2);
    Aerogel->SetMaterialPropertiesTable(mptAerogel);

    //NaI
    G4double energyNaI[2] = {1.239841939*eV/0.2, 1.239841939*eV/0.9}; // TO EXTEND
    G4double rindexNaI[2] = {1.78, 1.78}; // TO EXTEND
    G4double fractionNaI[2] = {1.0, 1.0}; // TO EXTEND
    NaI = new G4Material("NaI", 3.67*g/cm3, 2);
    NaI->AddElement(Na, 1);
    NaI->AddElement(I, 1);
    G4MaterialPropertiesTable *mptNaI = new G4MaterialPropertiesTable();
    mptNaI->AddProperty("RINDEX", energyNaI, rindexNaI, 2);
    mptNaI->AddProperty("FASTCOMPONENT", energyNaI, fractionNaI, 2);
    mptNaI->AddConstProperty("SCINTILLATIONYIELD",38./keV);
    mptNaI->AddConstProperty("RESOLUTIONSCALE",1.0);
    mptNaI->AddConstProperty("FASTTIMECONSTANT", 250.*ns);
    mptNaI->AddConstProperty("YIELDRATIO",1.);
    NaI->SetMaterialPropertiesTable(mptNaI);

    //LYSO
    LYSO = new G4Material ("LYSO", 7.1 * g / cm3, 3, kStateSolid);
    LYSO->AddElement (Lu, 2);
    LYSO->AddElement (Si, 1);
    LYSO->AddElement (O, 5);

    const G4int NUMENTRIES_1_LYSO = 261;
    G4double FAST_Energy_LYSO[NUMENTRIES_1_LYSO] = {
      1.77169 * eV, 1.77266 * eV, 1.77558 * eV, 1.77851 * eV, 1.78145 * eV, 1.78539 * eV, 1.79033 * eV, 1.7963 * eV, 1.80231 * eV, 1.80836 * eV, 1.81445 * eV, 1.82058 * eV, 1.82882 * eV, 1.83401 * eV, 1.84553 * eV, 1.85293 * eV, 1.86147 * eV, 1.869 * eV, 1.87769 * eV, 1.89308 * eV, 1.90536 * eV, 1.92007 * eV, 1.93039 * eV, 1.94901 * eV, 1.95846 * eV, 1.9668 * eV, 1.97884 * eV, 1.99102 * eV, 2.00088 * eV, 2.01209 * eV, 2.02596 * eV, 2.03617 * eV, 2.04519 * eV, 2.0569 * eV, 2.06611 * eV, 2.0794 * eV, 2.09151 * eV, 2.10239 * eV, 2.112 * eV, 2.1231 * eV, 2.13431 * eV, 2.14565 * eV, 2.15566 * eV, 2.16868 * eV, 2.18038 * eV, 2.19519 * eV, 2.21171 * eV, 2.2193 * eV, 2.23619 * eV, 2.23464 * eV, 2.24395 * eV, 2.25806 * eV, 2.27234 * eV, 2.28358 * eV, 2.29493 * eV, 2.30475 * eV, 2.31631 * eV, 2.32463 * eV, 2.33134 * eV, 2.33809 * eV, 2.34487 * eV, 2.35856 * eV, 2.36719 * eV, 2.37939 * eV, 2.38642 * eV, 2.40238 * eV, 2.41134 * eV, 2.424 * eV, 2.43312 * eV, 2.44047 * eV, 2.44786 * eV, 2.46278 * eV, 2.47788 * eV, 2.48741 * eV, 2.49317 * eV, 2.49702 * eV, 2.50282 * eV, 2.50865 * eV, 2.5145 * eV, 2.52038 * eV, 2.52432 * eV, 2.53223 * eV, 2.5362 * eV, 2.54619 * eV, 2.55424 * eV, 2.56031 * eV, 2.56437 * eV, 2.57049 * eV, 2.57663 * eV, 2.58487 * eV, 2.59317 * eV, 2.59734 * eV, 2.60571 * eV, 2.61414 * eV, 2.61414 * eV, 2.61837 * eV, 2.62262 * eV, 2.62475 * eV, 2.62902 * eV, 2.63331 * eV, 2.63545 * eV, 2.63976 * eV, 2.64191 * eV, 2.64841 * eV, 2.65493 * eV, 2.6593 * eV, 2.66149 * eV, 2.66588 * eV, 2.67914 * eV, 2.67914 * eV, 2.68136 * eV, 2.68136 * eV, 2.68359 * eV, 2.68805 * eV, 2.68805 * eV, 2.68805 * eV, 2.69477 * eV, 2.69477 * eV, 2.69702 * eV, 2.70153 * eV, 2.70605 * eV, 2.71286 * eV, 2.71742 * eV, 2.71971 * eV, 2.722 * eV, 2.722 * eV, 2.72429 * eV, 2.72889 * eV, 2.72889 * eV, 2.73351 * eV, 2.73814 * eV, 2.74279 * eV, 2.74512 * eV, 2.74979 * eV, 2.75213 * eV, 2.75447 * eV, 2.75917 * eV, 2.75682 * eV, 2.76389 * eV, 2.76626 * eV, 2.76389 * eV, 2.76626 * eV, 2.77338 * eV, 2.77576 * eV, 2.78533 * eV, 2.79255 * eV, 2.79738 * eV, 2.80223 * eV, 2.80466 * eV, 2.80709 * eV, 2.80953 * eV, 2.80953 * eV, 2.81934 * eV, 2.8218 * eV, 2.82673 * eV, 2.83168 * eV, 2.84164 * eV, 2.84916 * eV, 2.85419 * eV, 2.8643 * eV, 2.86684 * eV, 2.87449 * eV, 2.87705 * eV, 2.87961 * eV, 2.88475 * eV, 2.88733 * eV, 2.8925 * eV, 2.89509 * eV, 2.90028 * eV, 2.90549 * eV, 2.90811 * eV, 2.91073 * eV, 2.91335 * eV, 2.91335 * eV, 2.91335 * eV, 2.91861 * eV, 2.92125 * eV, 2.92125 * eV, 2.92389 * eV, 2.92654 * eV, 2.92654 * eV, 2.92919 * eV, 2.92919 * eV, 2.93185 * eV, 2.93451 * eV, 2.93717 * eV, 2.93985 * eV, 2.94252 * eV, 2.9452 * eV, 2.94789 * eV, 2.94789 * eV, 2.94789 * eV, 2.95058 * eV, 2.95868 * eV, 2.96411 * eV, 2.96955 * eV, 2.97228 * eV, 2.97228 * eV, 2.96955 * eV, 2.97228 * eV, 2.97502 * eV, 2.97776 * eV, 2.97502 * eV, 2.9805 * eV, 2.9805 * eV, 2.9805 * eV, 2.98601 * eV, 2.99154 * eV, 2.99431 * eV, 2.99431 * eV, 2.99708 * eV, 2.99431 * eV, 2.99708 * eV, 3.00544 * eV, 3.00824 * eV, 3.00824 * eV, 3.00824 * eV, 3.00824 * eV, 3.01385 * eV, 3.0223 * eV, 3.02797 * eV, 3.03081 * eV, 3.02797 * eV, 3.03365 * eV, 3.03081 * eV, 3.03081 * eV, 3.0365 * eV, 3.03935 * eV, 3.04221 * eV, 3.04795 * eV, 3.04795 * eV, 3.05083 * eV, 3.05371 * eV, 3.05949 * eV, 3.06239 * eV, 3.06529 * eV, 3.0682 * eV, 3.06529 * eV, 3.07112 * eV, 3.0682 * eV, 3.07696 * eV, 3.08283 * eV, 3.0976 * eV, 3.09464 * eV, 3.09464 * eV, 3.10653 * eV, 3.11252 * eV, 3.11852 * eV, 3.12757 * eV, 3.13668 * eV, 3.14583 * eV, 3.15813 * eV, 3.16741 * eV, 3.17675 * eV, 3.20828 * eV, 3.23719 * eV, 3.26664 * eV, 3.28656 * eV, 3.31351 * eV, 3.34783 * eV, 3.38287 * eV,
    };
    G4double FAST_COMPONENT_LYSO[NUMENTRIES_1_LYSO] = {
      0.011691,  0.011691,  0.011691,  0.0146138,  0.0146138,  0.0146138,  0.011691,  0.011691,  0.00876827,  0.00876827,  0.00584551,  0.00584551,  0.00584551,  0.00292276,  0.00876827,  0.0146138,  0.0146138,  0.0146138,  0.0204593,  0.023382,  0.0263048,  0.0204593,  0.0204593,  0.023382,  0.0292276,  0.0321503,  0.0350731,  0.0379958,  0.0379958,  0.0379958,  0.0350731,  0.0379958,  0.0409186,  0.0438413,  0.0526096,  0.0584551,  0.0643006,  0.0730689,  0.0730689,  0.0818372,  0.0906054,  0.0964509,  0.0993737,  0.105219,  0.111065,  0.122756,  0.125678,  0.146138,  0.146138,  0.160752,  0.157829,  0.163674,  0.184134,  0.192902,  0.20167,  0.219207,  0.230898,  0.242589,  0.25428,  0.265971,  0.274739,  0.292276,  0.306889,  0.315658,  0.321503,  0.350731,  0.368267,  0.385804,  0.397495,  0.415031,  0.432568,  0.458873,  0.482255,  0.496868,  0.514405,  0.529019,  0.549478,  0.564092,  0.581628,  0.593319,  0.602088,  0.616701,  0.637161,  0.660543,  0.681002,  0.71023,  0.736534,  0.756994,  0.777453,  0.806681,  0.844676,  0.868058,  0.891441,  0.9119,  0.938205,  0.955741,  0.984969,  1.0142,  1.03173,  1.05511,  1.07557,  1.11649,  1.13695,  1.15741,  1.17495,  1.19248,  1.21002,  1.22756,  1.27432,  1.2977,  1.31524,  1.32985,  1.36785,  1.40292,  1.39415,  1.4,  1.41754,  1.44092,  1.47015,  1.48476,  1.50814,  1.5286,  1.54906,  1.56952,  1.58998,  1.61921,  1.63967,  1.66597,  1.68935,  1.71566,  1.73904,  1.76242,  1.77996,  1.80042,  1.8238,  1.83549,  1.85303,  1.8618,  1.87933,  1.89979,  1.91733,  1.92902,  1.95825,  1.98163,  2.01378,  2.03424,  2.0547,  2.07808,  2.09562,  2.11023,  2.12484,  2.13361,  2.15407,  2.15699,  2.15992,  2.16576,  2.16868,  2.16868,  2.16284,  2.15699,  2.14823,  2.13946,  2.12484,  2.11023,  2.08977,  2.06639,  2.04593,  2.02839,  2.01086,  1.98455,  1.96409,  1.94948,  1.93194,  1.91733,  1.90271,  1.87641,  1.86472,  1.8501,  1.83841,  1.82088,  1.79749,  1.77119,  1.75073,  1.73027,  1.70689,  1.68058,  1.65428,  1.6309,  1.60167,  1.57244,  1.55491,  1.53152,  1.50522,  1.47891,  1.45261,  1.43215,  1.40877,  1.38831,  1.362,  1.33862,  1.31232,  1.28601,  1.27432,  1.25678,  1.21587,  1.19541,  1.17203,  1.14864,  1.12234,  1.10772,  1.08434,  1.06096,  1.0142,  0.987891,  0.967432,  0.938205,  0.9119,  0.879749,  0.853445,  0.82714,  0.786221,  0.765762,  0.739457,  0.716075,  0.681002,  0.660543,  0.637161,  0.60501,  0.581628,  0.552401,  0.531942,  0.505637,  0.485177,  0.458873,  0.435491,  0.412109,  0.379958,  0.356576,  0.336117,  0.309812,  0.280585,  0.25428,  0.207516,  0.175365,  0.157829,  0.13737,  0.119833,  0.0993737,  0.0759916,  0.0613779,  0.0526096,  0.0350731,  0.0263048,  0.011691,  0.00876827,  0.00876827,  0.011691,  0.011691,  0.011691,  0.00876827,  0.011691,
    };

    const G4int NUMENTRIES_2_LYSO = 3;
    G4double RIND_Energy_LYSO[NUMENTRIES_2_LYSO]    = { 1.0 * eV, 1.84 * eV, 4.08 * eV };
    G4double RIND_INDEX_LYSO[NUMENTRIES_2_LYSO]     = { 1.82, 1.82, 1.82 };

    const G4int NUMENTRIES_3_LYSO = 9;
    G4double ABS_Energy_LYSO[NUMENTRIES_3_LYSO]     = { 1.00 * eV , 2.82 * eV , 2.88 * eV , 2.95 * eV , 3.02 * eV  , 3.10 * eV  , 3.18 * eV  , 3.26 * eV , 4.08 * eV };
    G4double ABS_LENGTH_LYSO[NUMENTRIES_3_LYSO]     = { 438.*mm , 438.*mm , 413.*mm , 375.*mm , 263.*mm  , 87.5 * mm  , 11.5 * mm  , 1.0 * mm  , 1.0 * mm  };

    G4MaterialPropertiesTable *mt_LYSO = new G4MaterialPropertiesTable();
    mt_LYSO->AddProperty ("FASTCOMPONENT", FAST_Energy_LYSO, FAST_COMPONENT_LYSO, NUMENTRIES_1_LYSO);
    mt_LYSO->AddProperty ("RINDEX",        RIND_Energy_LYSO, RIND_INDEX_LYSO,     NUMENTRIES_2_LYSO);
    mt_LYSO->AddProperty ("ABSLENGTH",     ABS_Energy_LYSO,  ABS_LENGTH_LYSO,     NUMENTRIES_3_LYSO);
    //mt->AddProperty("RAYLEIGH",      ABS_Energy,  Rayleigh,     NUMENTRIES_2);
    mt_LYSO->AddConstProperty ("SCINTILLATIONYIELD", 40000. / MeV);
    mt_LYSO->AddConstProperty ("RESOLUTIONSCALE", 3.4);
    mt_LYSO->AddConstProperty ("FASTTIMECONSTANT", 40.*ns);
    mt_LYSO->AddConstProperty ("YIELDRATIO", 1.0);
    mt_LYSO->AddConstProperty ("FASTSCINTILLATIONRISETIME", 0.1 * ns);
    LYSO->SetMaterialPropertiesTable (mt_LYSO);

    //BGO
    const G4int NUMENTRIES_BGO = 3;
    G4double BSO_Energy[NUMENTRIES_BGO] = {2.0*eV, 2.87*eV, 2.9*eV};
    BGO = new G4Material("BGO", 7.13*g/cm3, 3);
    BGO->AddElement(Bi, 4);
    BGO->AddElement(Ge, 3);
    BGO->AddElement(O, 12);
    G4double RIndexBGO[NUMENTRIES_BGO]={ 2.15, 2.15, 2.15};
    G4double Absorption_BGO[NUMENTRIES_BGO]={24.*cm, 24.*cm, 24.*cm}; //http://www.sciencedirect.com/science/article/pii/0167508784900930
    G4double ScintilFast_BGO[NUMENTRIES_BGO]={0.00, 0.00, 1.00}; //I don't know what this is or if it is right
    G4MaterialPropertiesTable* MPT_BGO = new G4MaterialPropertiesTable();
    MPT_BGO->AddProperty("RINDEX",BSO_Energy,RIndexBGO,NUMENTRIES_BGO);
    MPT_BGO->AddProperty("ABSLENGTH",BSO_Energy,Absorption_BGO,NUMENTRIES_BGO);
    MPT_BGO->AddProperty("FASTCOMPONENT",BSO_Energy,ScintilFast_BGO,NUMENTRIES_BGO);
    MPT_BGO->AddConstProperty("SCINTILLATIONYIELD",2000./MeV);
    MPT_BGO->AddConstProperty("RESOLUTIONSCALE",1.0);
    MPT_BGO->AddConstProperty("FASTTIMECONSTANT", 100.*ns);
    BGO->SetMaterialPropertiesTable(MPT_BGO);

    //SiliconResin
    SiliconResin = new G4Material ("SiliconResin", 1.060*g/cm3, 2);
    SiliconResin->AddElement (C, 2);
    SiliconResin->AddElement (H, 6);
    const G4int nEntries_SiliconResin = 2;
    G4double PhotonEnergySiliconResin[nEntries_SiliconResin] = {1.239841939*eV/0.2, 1.239841939*eV/0.9};
    G4double RefractiveIndexSiliconResin[nEntries_SiliconResin] = {1.46, 1.46};
    G4double AbsClad_SiliconResin[nEntries_SiliconResin]={ 20.0*m,20.0*m };
    G4MaterialPropertiesTable* MPTSiliconResin = new G4MaterialPropertiesTable();
    MPTSiliconResin->AddProperty("RINDEX",PhotonEnergySiliconResin,RefractiveIndexSiliconResin,nEntries_SiliconResin);
    MPTSiliconResin->AddProperty("ABSLENGTH",PhotonEnergySiliconResin,AbsClad_SiliconResin,nEntries_SiliconResin);
    SiliconResin->SetMaterialPropertiesTable(MPTSiliconResin);



    //Epoxy common
    const G4int nEntries_EpoxyResin = 2;
    G4double PhotonEnergyEpoxyResin[nEntries_EpoxyResin] = {1.239841939*eV/0.2, 1.239841939*eV/0.9};
    G4double RefractiveIndexEpoxyResin[nEntries_EpoxyResin] = {1.53, 1.53};
    G4MaterialPropertiesTable* MPTEpoxyResin = new G4MaterialPropertiesTable();
    MPTEpoxyResin->AddProperty("RINDEX",PhotonEnergyEpoxyResin,RefractiveIndexEpoxyResin,nEntries_EpoxyResin);

    //Epoxy0
    Epoxy0 = new G4Material (" Epoxy ", 2*g/cm3 , 4);
    Epoxy0 -> AddElement ( C , 12);
    Epoxy0 -> AddElement ( H , 14);
    Epoxy0 -> AddElement ( O , 2);
    Epoxy0 -> AddElement ( N , 4);
    Epoxy0 -> SetMaterialPropertiesTable(MPTEpoxyResin);

    //Epoxy1
    Epoxy1 = new G4Material (" Epoxy ", 1*g/cm3 , 4);
    Epoxy1 -> AddElement ( C , 12);
    Epoxy1 -> AddElement ( H , 14);
    Epoxy1 -> AddElement ( O , 2);
    Epoxy1 -> AddElement ( N , 4);
    Epoxy1 -> SetMaterialPropertiesTable(MPTEpoxyResin);

    //Epoxy2
    Epoxy2 =	new G4Material("Epoxy",	1.2*g/cm3,	4);
    Epoxy2->AddElement(C , 27);
    Epoxy2->AddElement(H , 32);
    Epoxy2->AddElement(O , 4);
    Epoxy2->AddElement(N , 2);
    Epoxy2 -> SetMaterialPropertiesTable(MPTEpoxyResin);

    //Epoxy3
    //The main component of epoxy resin commonly used to insulate magnet coils.
    G4Material *tmpMaterial = new G4Material("aralditef",1.175*g/cm3, 3, kStateSolid);
    tmpMaterial->AddElement(C, 12);
    tmpMaterial->AddElement(H, 18);
    tmpMaterial->AddElement(O, 4);
    //A hardener for the epoxy resin
    G4Material *tmpMaterial1 = new G4Material("hy906", 1.225*g/cm3, 3, kStateSolid);
    tmpMaterial1->AddElement(C, 10);
    tmpMaterial1->AddElement(H, 5);
    tmpMaterial1->AddElement(O, 3);
    //An accelerator for epoxy resin
    G4Material *tmpMaterial2 = new G4Material("dy061", 1.025*g/cm3, 4, kStateSolid);
    tmpMaterial2->AddElement(C, 15);
    tmpMaterial2->AddElement(H, 25 );
    tmpMaterial2->AddElement(O, 1 );
    tmpMaterial2->AddElement(N, 3 );
    //Material type 3 from CERN 81-05, "The Selection and Properties of Epoxide Resins Used for the Insulation of Magnet Systems in Radiation Environments".
    Epoxy3 = new G4Material("epoxyresin3", 1.20*g/cm3, 3, kStateSolid);
    Epoxy3->AddMaterial(tmpMaterial,49.7512*perCent);
    Epoxy3->AddMaterial(tmpMaterial1,49.7512*perCent);
    Epoxy3->AddMaterial(tmpMaterial2,00.4976*perCent);
    Epoxy3 -> SetMaterialPropertiesTable(MPTEpoxyResin);

//mirrorSurface
    mirrorSurface = new G4OpticalSurface("mirrorSurface");
    G4double energy_mirror[2] = {1.239841939*eV/0.2, 1.239841939*eV/0.9}; // TO EXTEND
    G4double reflectivity_mirror[2] = {0.1, 0.1};
    G4MaterialPropertiesTable *mptMirror = new G4MaterialPropertiesTable();
    mptMirror->AddProperty("REFLECTIVITY", energy_mirror, reflectivity_mirror, 2);
    mirrorSurface->SetMaterialPropertiesTable(mptMirror);
    mirrorSurface->SetType(dielectric_metal);
    mirrorSurface->SetFinish(ground);
    mirrorSurface->SetModel(unified);

  }

  G4VPhysicalVolume *MyDetectorConstruction::Construct()
  {
    //Construct World
    G4double xWorld = (xpitch*nx+xgap*(nx+1))*0.5*um;
    G4double yWorld = (ypitch*ny+ygap*(ny+1))*0.5*um;
    G4double zWorld = (2*radthick+DUTthick)*um;
    solidWorld = new G4Box("solidWorld", xWorld, yWorld, zWorld);
    logicWorld = new G4LogicalVolume(solidWorld, Air, "logicWorld");
    physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);

    //Construct Radiator
    solidRadiator = new G4Box("solidRadiator", xWorld, yWorld, radthick*0.5*um);
    logicRadiator = new G4LogicalVolume(solidRadiator, Epoxy2, "logicalRadiator");
    G4Colour blue(0., 0., 1.);
    G4VisAttributes* blueVisAttributes = new G4VisAttributes(blue);
    logicRadiator->SetVisAttributes(blueVisAttributes);
    skin = new G4LogicalSkinSurface("skin", logicWorld, mirrorSurface);
    fScoringVolume = logicRadiator;
    physRadiator = new G4PVPlacement(0, G4ThreeVector(0., 0., radthick*1.5*um), logicRadiator, "physRadiator", logicWorld, false, 0, true);

    //Contruct Detector
    solidDetector = new G4Box("solidDetector", xpitch*0.5*um, ypitch*0.5*um, DUTthick*0.5*um);
    logicDetector = new G4LogicalVolume(solidDetector, Air, "logicDetector");
    G4Colour brown(0.7, 0.4, 0.1);
    G4VisAttributes* brownVisAttributes = new G4VisAttributes(brown);
    logicDetector->SetVisAttributes(brownVisAttributes);
    G4int i1 = 1;
    G4int j1 = 1;
    for(G4int i = 1; i <= nx; i++)
    {
      for(G4int j = 1; j <= ny; j++)
      {
        physDetector = new G4PVPlacement(0, G4ThreeVector((i1*xpitch*0.5)*um + xgap*i*um - (xpitch*nx+xgap*(nx+1))*0.5*um, (j1*ypitch*0.5)*um + ygap*j*um - (ypitch*ny+ygap*(ny+1))*0.5*um , (2*radthick+DUTthick*0.5)*um), logicDetector, "physDetector", logicWorld, false, j+i*nx, true);
        j1+=2;
      }
      i1+=2;
      j1=1;
    }

    return physWorld;
  }

  void MyDetectorConstruction::ConstructSDandField()
  {
    MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");

    logicDetector->SetSensitiveDetector(sensDet);
  }
