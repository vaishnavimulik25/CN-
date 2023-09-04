#include<stdio.h>
#include"functions.h"
#include<stdlib.h>
#include<string.h>
#include <stdint.h>
#include <inttypes.h>
#include <arpa/inet.h>
#include<math.h>

int main(){

//    printf("PART A\n");
//    char class1;
//    printf("Enter the class\n");
//    scanf("%c",&class1);
//    
//    switch(class1){
//
//        case'A': printf("255.0.0.0\n");
//                 break;
//
//        case'B': printf("255.255.0.0\n");
//                 break;
//                
//        case'C': printf("255.255.0.0\n");
//                 break;
//
//        default:
//                 break;
//    }
//    
//    printf("----------------------------------------------------------------\n\n"); 
//    printf("PART B\n");
    char IPaddress[14];
    char subnetCIDR[3];
    
    printf("Enter IP address\n");
    scanf("%s",IPaddress);
//    printf("%s",IPaddress);
    printf("Enter CIDR notation of subnet mask\n");
    scanf("%s",subnetCIDR);
//    printf("%s",subnetCIDR);

    printf("----------------------------------------------------------------\n\n");
    char class = FindClass(IPaddress);
    //printf("%c",class);
    int totalhosts = FindTotalHosts(class);
    //printf("%d",totalhosts);
    int bits = FindSubnetFromClass(class);
    //printf("%d",bits);
   int mask = 0;
   for(int i = 0; i < 2; i++){
     //  printf("%c\n",subnetCIDR[i]);
       mask = mask*10 + subnetCIDR[i] - '0';
   // printf("%d\n",mask);
   }
    //printf("%d",mask);
    int subnet = FindSubnets(mask,bits);
    printf("Number of subnets  %d\n",subnet);
//
    int hosts = FindHostperSubnet(totalhosts,subnet);
    printf("Number of hosts    %d\n", hosts);
//
    char* NWid = FindNWid(class,IPaddress);
    printf("N/W id             %s\n",NWid);
//
    char* Broadcastid = FindBCaddress(class,IPaddress);
    printf("Broadcastid        %s\n\n",Broadcastid);
//
    calculateAndPrintSubnetRanges(IPaddress,mask,subnet);

    return 0;
}

