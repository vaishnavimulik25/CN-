
char FindClass(char Ip[14]);

int FindTotalHosts(char class);

int FindSubnetFromClass(char class);

int FindSubnets(int mask, int subnets);
int FindHostperSubnet(int totalhosts, int totalsubnets);
char* FindNWid(char class, char ip[14]);
char* FindBCaddress(char class, char ip[14]);
void calculateAndPrintSubnetRanges(const char *ipString, int subnetMaskLength, int numSubnets);
