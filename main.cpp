#include <iostream>
#include <unistd.h>
#include <cstring>
#include <gpib/ib.h>
#include <gpib/gpib_user.h>
using namespace std;

#define TRUE 1
#define FALSE 0
int InitGPIB(void);
int SendStringGPIB(char *x);
int userDescriptor;

int InitGPIB()
{
    int boardIndex=0;
    int primaryAddress = 4;
    int secondaryAddress=0;
    int gpibTimeout = T3s;
    int EOImode = 1;
    int EOSmode = 0;
    userDescriptor = ibdev(boardIndex,
    primaryAddress,
    secondaryAddress,
    gpibTimeout,
    EOImode,
    EOSmode);
    if (userDescriptor<0) return -1;
    return 0;
}

int SendStringGPIB(char *x)
{
    ibwrt(userDescriptor,x,strlen(x));
    if (ibsta & ERR)
    {
        printf("Send string error. String is %s. ibsta=0x%x\n",x,ibsta);
        return -1;
    }
    return 0;
}

int main()
{

    int status;
    // Start GPIB:
    status = InitGPIB();
    if (status < 0)
    {
        printf("GPIB detection error\n");
        sleep(2);
        return 0;
    }
    // /////////////////////////////////////////////////////////////////////
    SendStringGPIB("L<xM=1<\r\n");
    cout << "Set to enhanced mode" << endl;
    // /////////////////////////////////////////////////////////////////////
    // LOAD
    char stas[100];

    SendStringGPIB("H\r\n"); // Turn controller to stop and stand-by state.
    SendStringGPIB("L\r\n"); // Send load mode command.
    SendStringGPIB("Ae1<\r\n"); // Select track second axis.
    SendStringGPIB("Pxet=180<\r\n"); // Select second target: 351.8 degre
    SendStringGPIB("Ded<\r\n"); // Set direction of second axis to be short
    SendStringGPIB("Vxe=5<\r\n"); // Set second velocity to 5
    SendStringGPIB("MT\r\n"); // Set motion mode to track to target.
    SendStringGPIB("H\r\n"); // Turn controller to stand-by state.

    // CONTROL
    SendStringGPIB("S\r\n");

    SendStringGPIB("XAe1<\r\n");
    ibwrt(userDescriptor,stas,strlen(stas));
    for(int i=0;i<strlen(stas); i++) cout << stas[i];
    cout << endl;

    SendStringGPIB("XPet<\r\n");
    ibwrt(userDescriptor,stas,strlen(stas));
    for(int i=0;i<strlen(stas); i++) cout << stas[i];
    cout << endl;

    SendStringGPIB("XD<\r\n");
    ibwrt(userDescriptor,stas,strlen(stas));
    for(int i=0;i<strlen(stas); i++) cout << stas[i];
    cout << endl;

    SendStringGPIB("XVe<\r\n");
    ibwrt(userDescriptor,stas,strlen(stas));
    for(int i=0;i<strlen(stas); i++) cout << stas[i];
    cout << endl;

    SendStringGPIB("H\r\n");

    // MOVE
    sleep(10);
    SendStringGPIB("G\r\n");


    // /////////////////////////////////////////////////////////////////////
    ibonl(userDescriptor,FALSE);
    cout << "Fine" << endl;
    // /////////////////////////////////////////////////////////////////////



    return 0;
}
