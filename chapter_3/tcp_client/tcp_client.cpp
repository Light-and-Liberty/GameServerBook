// tcp_client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "../ImaysNet/ImaysNet.h"
#include <chrono>
#include <thread>

using namespace std;

int main()
{
	try
	{
		Socket s(SocketType::Tcp);		// 1
		s.Bind(Endpoint::Any);		// 2
		cout << "Connecting to server...\n";
		s.Connect(Endpoint("127.0.0.1", 5959)); // 3 <===여기다가 실제 여러분들이 원하는 주소를 넣으십시오. 127.0.0.1은 로컬 기기를 뜻합니다.

		// 4
		cout << "Sending data...\n";
		const char* text = "hello";
		// 보낼 문자열의 sz도 포함해서 전송해야 하므로 +1 합니다.
		s.Send(text, strlen(text) + 1); 

		// 위 송신 함수가 성공하더라도 이것은 소켓에 송신 데이터를 넣은 것일 뿐,
		// 아직 서버에 도착했다는 뜻은 아닙니다.
		// 이 상태에서 바로 소켓 닫기를 해 버리면 서버는 데이터를 받지 못하는 가능성도 있습니다.
		// 따라서 의도적으로 서버가 받을 수 있는 충분한 시간을 기다립니다.
		// 본 예시 프로그램은 독자의 이해를 위한 것일 뿐, 여러분이 실전에서 이렇게 만드실 일은 별로 없을 것입니다.
		std::this_thread::sleep_for(1s);

		// 5
		cout << "Closing socket...\n";
		s.Close();       
	}
	catch (Exception& e)
	{
		cout << "Exception! " << e.what() << endl;
	}
	return 0;
}

