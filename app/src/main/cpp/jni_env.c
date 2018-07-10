//
// Created by user on 18-6-12.
//

#include <jni.h>
#include "com_example_user_jnistudy_JniUtil.h"


//JNIEnv 结构体的指针别名
typedef struct MyJNINativeInterface_* MyJNIEnv;

//结构体
struct MyJNINativeInterface_{
    char* (*MyNewStringUTF)(MyJNIEnv*,char*);
};

//结构体中函数指针实现
char* MyNewStringUTF(MyJNIEnv* env,char* str){
    //在newStringUTF执行过程中，仍然需要JNIEnv，此处只是简单的示范
    return str;
}

JNIEXPORT jstring JNICALL
Java_com_example_user_jnistudy_JniUtil_myJNIEnv(
                          JNIEnv *env,jclass cls) {
//    实例化结构体
    struct MyJNINativeInterface_ struct_env;
//    函数指针赋值
    struct_env.MyNewStringUTF = MyNewStringUTF;
//    结构体指针别名
    MyJNIEnv e = &struct_env;
//    结构体二级指针
    MyJNIEnv *env1 = &e;

//    通过二级指针调用函数
    LOG_D("%s",(*env1)->MyNewStringUTF(env1,"my_jni_env"));

    return (*env)->NewStringUTF(env,"abd");

}
