#include "lidarFormat.h"
#include <iostream>
#include <stdio.h>
#include <string.h>

lidarFormat::lidarFormat()
{
	std::cout << "hello lidarformat!" << std::endl;
	


}

lidarFormat::~lidarFormat()
{
}


const char *lidarFormat::opensession(){
	const char *opensession = "\x02\x02\x02\x02" // STX
						"\x00\x00\x00\x0E"  // Length: 13 bytes
						"\x00\x00"          // Hub and NoC
						"\x00\x00\x00\x00"  // SessionID
						"\x00\x01"          // ReqID
						"\x4F\x58"          // Cmd = "O", Mode = "X"
						"\x1E"              // Timeout = 30 sec
						"\x00\x01"
						"\x00";         // ClientID Length = 0, ClientID Flexstring = 0
	return opensession;
}

char *lidarFormat::callinitializepose(const char *session_id, const char *pose){
	char initpose[1024] = "\x02\x02\x02\x02"  // STX
						  "\x00\x00\x00\x2C"  // Length: 44 bytes
						  "\x00\x00";

	memcpy(&initpose[10], session_id, 4);
	const char *middle_data = "\x00\x02"          // ReqID
                            "\x4D\x4E"          // Cmd = "M", Mode = "N"
                            "\x4C\x6F\x63\x49\x6E\x69\x74\x69\x61\x6C\x69\x7A\x65\x41\x74\x50\x6F\x73\x65"  // Method name: "LocInitializeAtPose"
                            "\x20";              // Space
	memcpy(&initpose[13], middle_data,24);
	memcpy(&initpose[37], pose, 12);
	const char *subsequent_data = "\x03\xE8";
	memcpy(&initpose[49], subsequent_data, 2);

	char *initializepose = &initpose[0];
	return initializepose;
}

char *lidarFormat::closesession(char *session_id){
	char close_session_data[1024] = "\x02\x02\x02\x02"  // STX
							   "\x00\x00\x00\x0A"  // Length: 10 bytes
							   "\x00\x00";          // Hub and NoC
	memcpy(&close_session_data[10], session_id, 4);

	const char *close_session_subsequent_data= "\x00\x03"          // ReqID
											   "\x43\x58";         // Cmd = "C", Mode = "X"

	memcpy(&close_session_data[14], close_session_subsequent_data, 4);

	char *closesession = &close_session_data[0];

	return closesession;


}





