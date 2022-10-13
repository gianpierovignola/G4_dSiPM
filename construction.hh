#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4OpticalSurface.hh"
#include "G4GenericMessenger.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

#include "globals.hh"
#include "G4Material.hh"


#include "G4LogicalSkinSurface.hh"

#include "detector.hh"
#include "MyMaterials.hh"

class MyDetectorConstruction : public G4VUserDetectorConstruction
{
public:
    MyDetectorConstruction();
    ~MyDetectorConstruction();

    G4LogicalVolume *GetScoringVolume() const { return fScoringVolume; }

    virtual G4VPhysicalVolume *Construct();

private:
    G4Box *solidWorld, *solidRadiator, *solidDetector;
    G4LogicalVolume *logicWorld, *logicRadiator, *logicDetector;
    G4VPhysicalVolume *physWorld, *physDetector, *physRadiator;

    G4OpticalSurface *mirrorSurface;

    G4Material *SiO2, *H2O, *Aerogel, *worldMat, *NaI, *LYSO, *BGO, *Silicone;
    G4Element *C, *Na, *I, *Bi, *Ge, *O;

    void DefineMaterials();
    virtual void ConstructSDandField();

    G4GenericMessenger *fMessenger;

    G4LogicalVolume *fScoringVolume;

    G4int nx, ny, xgap, ygap, xpitch, ypitch, radthick, DUTthick;

    //per Silicone
    G4NistManager*     nistMan;
};

#endif
