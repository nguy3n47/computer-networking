// Server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Server.h"
#include "afxsock.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;

//Kiem tra co phai la so nguyen to hay khong
bool isPrime(int n) {
	if (n < 2)
		return false;
	for (int i = 2; i <= (int)sqrt((float)n); i++) {
		if (n % i == 0) {
			return false;
		}
	}
	return true;
}

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		_tprintf(_T("Fatal Error: MFC initialization failed\n"));
		nRetCode = 1;
	}
	else
	{
		// TODO: code your application's behavior here.
		CSocket server;
		unsigned int port = 1234;
		int i;
		AfxSocketInit(NULL);

		server.Create(port);
		server.Listen(5);

		//Nhap so luong client
		printf("\n Nhap so luong Client: ");
		int num_client;
		scanf("%d", &num_client);
		printf("\n Dang lang nghe ket noi tu Client...\n");
		//Tao mang chua cac socket client
		CSocket* sockClients = new CSocket[num_client];
		for (i = 0; i < num_client; i++) {
			int* numbers = new int[10];
			server.Accept(sockClients[i]);
			printf("Da tiep nhan client %d/%d\n", i + 1, num_client);
			//Bao cho client biet minh la client thu may
			sockClients[i].Send((char*)&i, sizeof(int), 0);
			sockClients[i].Receive((char*)&numbers[i], sizeof(int), 0);
			printf("Da nhan tu client %d lan 1, so %d\n", i + 1, numbers[i]);
			sockClients[i].Receive((char*)&numbers[i + num_client], sizeof(int), 0);
			printf("Da nhan tu client %d lan 2, so %d\n", i + 1, numbers[i + num_client]);
			/*printf("Tong : %d\n", numbers[i] + numbers[i + num_client]);
			printf("Hieu : %d\n", numbers[i] - numbers[i + num_client]);
			printf("Nhan : %d\n", numbers[i] * numbers[i + num_client]);
			printf("Chia : %f\n", float(numbers[i]) / numbers[i + num_client]);*/
			printf("Gui ket qua cho client %d\n", i + 1);
			int sum = 0;
			int sub = 0;
			int mul = 1;
			float div = 1.0;
			//Cong - Tru - Nhan - Chia
			sum = numbers[i] + numbers[i + num_client];
			sub = numbers[i] - numbers[i + num_client];
			mul = numbers[i] * numbers[i + num_client];
			div = float(numbers[i]) / numbers[i + num_client];
			sockClients[i].Send((char*)&sum, sizeof(int), 0);
			sockClients[i].Send((char*)&sub, sizeof(int), 0);
			sockClients[i].Send((char*)&mul, sizeof(int), 0);
			sockClients[i].Send((char*)&div, sizeof(float), 0);
			//Ngat ket noi voi client do
			//sockClients[i].ShutDown(2); //Ngat ca chieu Gui va Nhan
			sockClients[i].Close();
		}
		getchar();
		server.Close();
	}
	getchar();
	return nRetCode;
}