#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <stdint.h>
#include <inttypes.h>
#include <arpa/inet.h>
#include<math.h>
#include"functions.h"

char FindClass(char Ip[]){
    
    char* token;
    char* ip;
    strcpy(ip,Ip);

    token = strtok(ip,".");
    
    int octet = 0;
    for(int i = 0; i< 3;i++){
        octet = octet*10 + Ip[i] - '0';
    }
    if(octet > 0 && octet < 127)
        return 'A';
    if(octet >= 128 && octet <= 191)
        return 'B';
    if(octet >= 192 && octet <= 223)
        return 'C';
}

int FindTotalHosts(char class){
    
    if(class == 'A')
        return 16777214;
    if(class == 'B')
        return 65534;
    if(class == 'C')
        return 254;
}

int FindSubnetFromClass(char class){

    if(class == 'A')
        return 8;
    if(class == 'B')
        return 16;
    if(class == 'C')
        return 24;
}

int FindSubnets(int mask, int subnets){
    return pow(2,mask - subnets);
}

int FindHostperSubnet(int totalhosts, int totalsubnets){
    return totalhosts/totalsubnets;
}

char* FindNWid(char class, char IP[14]){
    char ip[14];
    strcpy(ip,IP);
    char* NWid = (char*)malloc(sizeof(char)*16);
    char* token;
    char cat[] = ".0";

    if(class == 'A'){
        token = strtok(ip,".");
        strcat(NWid,token);
        strcat(NWid,cat);
        strcat(NWid,cat);
        strcat(NWid,cat);
        return NWid;
    }

    if(class == 'B'){
        token = strtok(ip,".");
        strcat(NWid,token);
        
        strcat(NWid, ".");
        
        token = strtok(NULL,".");
        strcat(NWid,token);
        
        strcat(NWid,cat);
        strcat(NWid,cat);
        return NWid;
    }
 
    if(class == 'C'){
        token = strtok((char*)ip,".");
        strcat(NWid,token);

        strcat(NWid, ".");
        
        token = strtok(NULL, ".");
        strcat(NWid,token);
        
        strcat(NWid, ".");
        
        token = strtok(NULL,".");
        strcat(NWid,token);
        
        strcat(NWid,cat);
        return NWid;
    }
}

char* FindBCaddress(char class, char IP[14]){
    char ip[14];
    strcpy(ip,IP);
    char* BCid = (char*)malloc(sizeof(char)*16);
    char* token = (char*)malloc(sizeof(char)*4);
    char cat[] = ".255";

    if(class == 'A'){
        token = strtok(ip,".");
        strcat(BCid,token);
        strcat(BCid,cat);
        strcat(BCid,cat);
        strcat(BCid,cat);
        return BCid;
    }

    if(class == 'B'){
        token = strtok(ip,".");
        strcat(BCid,token);
        
        strcat(BCid, ".");
        
        token = strtok(NULL,".");
        strcat(BCid,token);
        strcat(BCid,cat);
        strcat(BCid,cat);
        return BCid;
    }
 
    if(class == 'C'){
        token = strtok(ip,".");
        strcat(BCid,token);
        strcat(BCid, ".");
        
        token = strtok(NULL,".");
        strcat(BCid,token);
        
        strcat(BCid, ".");
        
        token = strtok(NULL,".");
        strcat(BCid,token);
        
        strcat(BCid,cat);
        return BCid;
    }
}

void calculateAndPrintSubnetRanges(const char *ipString, int subnetMaskLength, int numSubnets) {
    uint32_t ipInteger;

    if (inet_pton(AF_INET, ipString, &ipInteger) != 1) {
        printf("Invalid IPv4 address format\n");
        return;
    }

    uint32_t subnetMask = 0xFFFFFFFF << (32 - subnetMaskLength);
    uint32_t subnetSize = 1 << (32 - subnetMaskLength);

    printf("Subnet Ranges:\n");

    for (int i = 0; i < numSubnets; i++) {
        uint32_t subnetStart = (ipInteger & subnetMask) + 1; // Add 1 for the first usable host
        uint32_t subnetEnd = subnetStart + subnetSize - 3;   // Subtract 3 for the network, broadcast, and first usable host

        printf("Subnet %d: %" PRIu32 ".%" PRIu32 ".%" PRIu32 ".%" PRIu32 " to %" PRIu32 ".%" PRIu32 ".%" PRIu32 ".%" PRIu32 "\n",
               i + 1,
               (subnetStart >> 24) & 0xFF, (subnetStart >> 16) & 0xFF, (subnetStart >> 8) & 0xFF, subnetStart & 0xFF,
               (subnetEnd >> 24) & 0xFF, (subnetEnd >> 16) & 0xFF, (subnetEnd >> 8) & 0xFF, subnetEnd & 0xFF);

        ipInteger += subnetSize; // Move to the next subnet
    }
}

