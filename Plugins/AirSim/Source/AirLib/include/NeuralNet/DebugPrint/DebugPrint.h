#pragma once

//木杉的博客 http://www.cnblogs.com/mushan    
//2012年6月10日    

#ifndef _DEBUGPRINTF_H_    
#define _DEBUGPRINTF_H_    
#define    WIN32_LEAN_AND_MEAN
#include<Windows.h>    
#include <tchar.h>    

//用于输出信息到编译器输出窗口的宏定义    
//使用win API，DEBUG版本会执行，RELEASE版本则不会    
//还可以使用DebugView，WinDbg等工具查看输出    


// 全都输出就好了
#define DP0(fmt) {TCHAR sOut[256];_stprintf_s(sOut,_T(fmt));OutputDebugString(sOut);}    
#define DP1(fmt,var) {TCHAR sOut[256];_stprintf_s(sOut,_T(fmt),var);OutputDebugString(sOut);}    
#define DP2(fmt,var1,var2) {TCHAR sOut[256];_stprintf_s(sOut,_T(fmt),var1,var2);OutputDebugString(sOut);}    
#define DP3(fmt,var1,var2,var3) {TCHAR sOut[256];_stprintf_s(sOut,_T(fmt),var1,var2,var3);OutputDebugString(sOut);}    


/*#ifdef _DEBUG    

#define DP0(fmt) {TCHAR sOut[256];_stprintf_s(sOut,_T(fmt));OutputDebugString(sOut);}    
#define DP1(fmt,var) {TCHAR sOut[256];_stprintf_s(sOut,_T(fmt),var);OutputDebugString(sOut);}    
#define DP2(fmt,var1,var2) {TCHAR sOut[256];_stprintf_s(sOut,_T(fmt),var1,var2);OutputDebugString(sOut);}    
#define DP3(fmt,var1,var2,var3) {TCHAR sOut[256];_stprintf_s(sOut,_T(fmt),var1,var2,var3);OutputDebugString(sOut);}    

#endif    

#ifndef _DEBUG    

#define DP0(fmt) ;    
#define DP1(fmt, var) ;    
#define DP2(fmt,var1,var2) ;    
#define DP3(fmt,var1,var2,var3) ;    

#endif  */  

#endif
