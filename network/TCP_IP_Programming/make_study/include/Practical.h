#ifndef _PRACTICAL_H_
#define _PRACTICAL_H_

// DieWithMessage.c에 정의됨
void DieWithUSerMessage(const char *msg, const char *detail);
void DieWithSystemMessage(const char *msg);

// TCPServerUtility.c에 정의됨
void HandleTCPClient(int clntSocket);

#endif
