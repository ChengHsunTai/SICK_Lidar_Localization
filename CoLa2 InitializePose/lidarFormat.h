#pragma once

class lidarFormat
{
public:
	lidarFormat();
	~lidarFormat();

	const char *opensession();
	char *callinitializepose(const char *session_id, const char *pose);
	char *closesession(char *session_id);
private:

};
