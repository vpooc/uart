//
// Created by ceshi on 2016/9/24.
//


#include "jni.h"
#include "jniLib.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <android/log.h>
#include <sys/ioctl.h>


#define JNI_AN_MainActivity        "com/fengbiaoedu/cy/myapplication/MainActivity"

#define METHOD_NUM 1
JNINativeMethod g_nativeMethod[METHOD_NUM] = {
        {"GetStrFromJNI", "()Ljava/lang/String;", (void *) GetStrFromJNI}
};

/*
 * 被虚拟机自动调用
 */
jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK)
        return JNI_ERR;

    jclass jClass = env->FindClass(JNI_AN_MainActivity);
    env->RegisterNatives(jClass, g_nativeMethod, METHOD_NUM);
    env->DeleteLocalRef(jClass);
    return JNI_VERSION_1_6;
}

void JNI_OnUnload(JavaVM *vm, void *reserved) {
    JNIEnv *env;
    int nJNIVersionOK = vm->GetEnv((void **) &env, JNI_VERSION_1_6);
    jclass jClass = env->FindClass(JNI_AN_MainActivity);
    env->UnregisterNatives(jClass);
    env->DeleteLocalRef(jClass);
}


int openUART() {

    int fd = open("/dev/tty", O_RDWR, O_NOCTTY, O_NDELAY);
    return fd;

}

void receiveMsgUART(int fd) {
    char buffer[255];
    char buf[255];
    int len, i = 0, k = 0;
    memset(buffer, 0, sizeof(buffer));
    memset(buf, 0, sizeof(buf));
    printf("\n");
    len = read(fd, buffer, 255);
    if (len > 0) {
        __android_log_print(ANDROID_LOG_INFO, "len","len=%d,buffer[0]=%c,buffer[1]=%c\n",len,buffer[0]),buffer[1];

        __android_log_print(ANDROID_LOG_INFO, "buffer", "buffer=%s\n", buffer);
    }

}



void closeUART(int fd) {
    close(fd);
}
jstring GetStrFromJNI(JNIEnv *env, jobject jobject1) {
    int d=openUART();
    receiveMsgUART(d);
    closeUART(d);


    return env->NewStringUTF("SSSSSS");
}




