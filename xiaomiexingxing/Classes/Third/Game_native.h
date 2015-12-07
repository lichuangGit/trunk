/*
** afp_native.h:
** 
** Copyright (C) 2005-2013 SKY-MOBI AS.  All rights reserved.
**
** Create date: 2012-7-9 by East.Ji
**
** This file is part of the sky avm library.
** It may not be redistributed under any circumstances.
*/

#ifndef __AFP_NATIVE_H__
#define __AFP_NATIVE_H__

#include <jni.h>
#include "../Ui/GameDialogLayer.h"
#if defined(__cplusplus)
extern "C" {
#endif
jint JNI_RegisterNativeFunctions(JNIEnv* env);

void setCallBack(std::function<void(int, int, map<int, int>)> func);
#if defined(__cplusplus)
}
#endif


#endif /* __AFP_NATIVE_H__ */
