
#include "com_example_user_jnistudy_JniUtil.h"

/*
 * c++函数名称 Java_完整类名_函数名
 *  在c++中JNIEnv为结构体别名,env为一级指针
 * */

JNIEXPORT jstring JNICALL
Java_com_example_user_jnistudy_JniUtil_stringFromJNI(
        JNIEnv *env,
        jclass cls) {
    std::string hello = "Hello from C++11";
    return env->NewStringUTF(hello.c_str());
}
