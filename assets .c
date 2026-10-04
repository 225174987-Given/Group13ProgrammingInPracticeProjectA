#include <stdio.h>
#include <string.h>
#include "assets.h"

struct Asset assets[MAX_ASSETS];
int assetCount = 0;

void calculateAssetStatus(){} // placeholder

int searchAssetById(int id){
    for(int i=0;i<assetCount;i++){
        if(assets[i].assetId == id) return i;
    }
    return -1;
}

void addAsset(){
    if(assetCount >= MAX_ASSETS){ printf("Register full!\n"); return; }
    struct Asset a;
    printf("\n--- ADD ASSET ---\n");
    printf("Asset ID: "); scanf("%d",&a.assetId);
    if(a.assetId <= 0){ printf("Invalid ID!\n"); return; }
    if(searchAssetById(a.assetId)!=-1){ printf("ID already exists!\n"); return; }

    printf("Asset Name: "); getchar(); fgets(a.assetName,50,stdin);
    a.assetName[strcspn(a.assetName,"\n")]=0;
    if(strlen(a.assetName)==0){ printf("Name empty!\n"); return; }

    printf("Type (Vehicle/Computer/Building/Equipment): ");
    fgets(a.assetType,30,stdin); a.assetType[strcspn(a.assetType,"\n")]=0;

    printf("Purchase Value N$: "); scanf("%lf",&a.purchaseValue);
    if(a.purchaseValue < 0){ printf("Negative value not allowed!\n"); return; }

    printf("Department: "); getchar(); fgets(a.department,30,stdin);
    a.department[strcspn(a.department,"\n")]=0;

    printf("Condition (Good/Fair/Poor): ");
    fgets(a.condition,20,stdin); a.condition[strcspn(a.condition,"\n")]=0;
    if(strcmp(a.condition,"Good")!=0 && strcmp(a.condition,"Fair")!=0 && strcmp(a.condition,"Poor")!=0){
        strcpy(a.condition,"Fair");
    }

    assets[assetCount++] = a;
    printf("Asset added! Total=%d\n",assetCount);
}

void displayAssets(){
    if(assetCount==0){ printf("No assets.\n"); return; }
    printf("\nID\tName\t\tType\t\tValue\t\tDept\tCondition\n");
    for(int i=0;i<assetCount;i++){
        printf("%d\t%s\t\t%s\t%.2f\t%s\t%s\n",assets[i].assetId,assets[i].assetName,assets[i].assetType,assets[i].purchaseValue,assets[i].department,assets[i].condition);
    }
}

void searchAsset(){
    int id; printf("Enter Asset ID to search: "); scanf("%d",&id);
    int idx=searchAssetById(id);
    if(idx!=-1) printf("FOUND: %s | %s | N$%.2f | %s\n",assets[idx].assetName,assets[idx].department,assets[idx].purchaseValue,assets[idx].condition);
    else printf("Not found.\n");
}

void assetReport(){
    double total=0; for(int i=0;i<assetCount;i++) total+=assets[i].purchaseValue;
    printf("\n--- ASSET REPORT ---\nTotal Assets: %d\nTotal Value: N$%.2f\n",assetCount,total);
}
