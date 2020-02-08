#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <string>
void writeDebug(const std::string &f);
int debugMsgID();
extern std::string debugString;

#ifdef DEBUG_0
#define MSG_2(A)
#define MSG_1(A)
#else

#ifdef  DEBUG_2
#define DEBUG_1
#define MSG_2(A) debugString += std::to_string(debugMsgID()) + "\tVERBOSE\t\t" +  A + '\n'
#else
#define MSG_2(A)
#endif

#ifdef  DEBUG_1
#define MSG_1(A) debugString += std::to_string(debugMsgID()) + "\tDEBUG\t\t" +  A + '\n' 
#else
#define MSG_1(A)
#endif

#endif
#endif
