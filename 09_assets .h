#ifndef ASSETS_H
#define ASSETS_H
#define MAX_ASSETS 100

struct Asset {
    int assetId;
    char assetName[50];
    char assetType[30];
    double purchaseValue;
    char department[30];
    char condition[20];
};

void addAsset();
void displayAssets();
void searchAsset();
int searchAssetById(int id);
void assetReport();

extern struct Asset assets[];
extern int assetCount;

#endif
