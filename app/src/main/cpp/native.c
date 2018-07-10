//
// Created by user on 18-6-11.
//
#include "com_example_user_jnistudy_JniUtil.h"
#include <stdlib.h>
#include <string.h>
/*
 * c函数名称 Java_完整类名_函数名
 *  在c中JNIEnv为结构体指针别名,env为二级指针
 * */

JNIEXPORT jstring JNICALL
Java_com_example_user_jnistudy_JniUtil_stringFromC(
        JNIEnv *env, jclass cls) {

    //为什么要传入env,函数执行过程中需要JNIEnv，代表Java运行环境
    //JNIEnv主要用来在C/C++中使用Java虚拟机的功能，比如：访问Java方法、属性，创建Java对象等等。
    //C++中为啥没有传入env,C++中有this
    //C++只是对C中那一套进行封装，

    //jobject 结构体
    //如果native方法不是静态方法，jobject代表该方法所属的java对象
    //如果native方法是静态方法，jobject代表该方法所属Java类的class对象 //TestNative.class

    //基本数据
//Java基本数据类型与JNI数据类型的映射关系（在C/C++中用特定的类型来表示Java的数据类型）
/*
boolean jboolean
byte jbyte
char jchar
short jshort
int jint
long jlong
float jfloat
double jdouble
void void
*/

//引用类型（对象）
//String jstring
//object jobject
//基本类型的数组也是引用类型
//byte[] jByteArray
//Class  jclass
    LOG_I("%s%d", "num = ", 12);
    LOG_D("我是debug信息。");
    LOG_E("%s%f", "我是浮点数:", 12.2);


    return (*env)->NewStringUTF(env, "c string ");
}

JNIEXPORT jstring JNICALL Java_com_example_user_jnistudy_JniUtil_accessFiled
        (JNIEnv *env, jobject obj){
//得到class
    jclass cls = (*env)->GetObjectClass(env, obj);
    //jfieldID
    //签名：类型的简称
    //属性，方法
    jfieldID fid = (*env)->GetFieldID(env, cls, "key", "Ljava/lang/String;");

    //获取key属性的值
    //注意：key为基本数据类型，规则如下
    //(*env)->GetIntField(); (*env)->Get<Type>Field();
    jstring jstr = (*env)->GetObjectField(env, obj, fid);


    //jstring转为 C/C++字符串
    char *str = (*env)->GetStringUTFChars(env, jstr, NULL);
    //拼接字符串
    char text[50] = "super ";
    strcat(text,str);

    //拼接完成之后，从C字符串转为jstring
    jstr = (*env)->NewStringUTF(env, text);

    //修改key的属性
    //注意规则：Set<Type>Field
    (*env)->SetObjectField(env, obj, fid, jstr);

    return jstr;
}

JNIEXPORT void JNICALL Java_com_example_user_jnistudy_JniUtil_accessStaticFiled
        (JNIEnv *env, jclass cls){
    jfieldID fid = (*env)->GetStaticFieldID(env, cls, "count", "I");
    //获取静态属性的值
    //规则：GetStatic<Type>Field
    jint  count = (*env)->GetStaticIntField(env,cls,fid);
    count += 10;
    //修改属性的值
    //规则：SetStatic<Type>Field
    (*env)->SetStaticIntField(env,cls,fid,count);
}

JNIEXPORT jint JNICALL Java_com_example_user_jnistudy_JniUtil_accessMethod
        (JNIEnv *env, jobject obj){
//如果native方法为static，jobject为子类jclass的实例，也就是native方法所属的类的Class实例
    jclass cls = (*env)->GetObjectClass(env,obj);

    jmethodID mid = (*env)->GetMethodID(env,cls,"getSumInt","(II)I");

    jint sum = (*env)->CallIntMethod(env,obj,mid,100,200);

    return sum;
}

JNIEXPORT void JNICALL Java_com_example_user_jnistudy_JniUtil_accessStaticMethod
        (JNIEnv *env, jclass cls, jstring path){

    jmethodID mid = (*env)->GetStaticMethodID(env,cls,"getFileName","()Ljava/lang/String;");

    jstring fileName = (*env)->CallStaticObjectMethod(env,cls,mid);

    char* cfileName = (*env)->GetStringUTFChars(env,fileName,NULL);
    char* cpath = (*env)->GetStringUTFChars(env,path,NULL);


    char filePath[100] = {0};

    sprintf(filePath,"%s%s",cpath,"jnis.txt");

    LOG_D("%s",cpath);
    FILE *fp = fopen(filePath,"w");
    fputs(cfileName,fp);
    fclose(fp);
}

JNIEXPORT void JNICALL Java_com_example_user_jnistudy_JniUtil_accessConstructor
        (JNIEnv *env, jclass class, jstring path){

    jclass cls = (*env)->FindClass(env,"java/util/Date");
    //构造方法jmethodID
    jmethodID contructor_mid = (*env)->GetMethodID(env, cls, "<init>","()V");
    //实例化一个Date对象
    jobject date_obj = (*env)->NewObject(env, cls, contructor_mid);

    //调用getTime方法
    jmethodID mid = (*env)->GetMethodID(env, cls, "getTime", "()J");
    jlong time = (*env)->CallLongMethod(env, date_obj, mid);

    char *time_str[50];
    sprintf(time_str,"%lld",time);

    char* cpath = (*env)->GetStringUTFChars(env,path,NULL);
    char filePath[100] = {0};

    sprintf(filePath,"%s%s",cpath,"jnis.txt");

    FILE *fp = fopen(filePath,"w");
    fputs(time_str,fp);
    fclose(fp);

}


//传入int数组，并对数组进行排序
JNIEXPORT void JNICALL Java_com_example_user_jnistudy_JniUtil_giveArray
        (JNIEnv *env, jclass cls, jintArray jintArray){
    //基本数据类型，传值
    //引用类型，传引用
    //arr，是指向Java数组的指针

    //Java的int数组(jintArray)->C int数组
    


}

////调用父类的方法
//JNIEXPORT void JNICALL Java_com_tz_jni_TestNative_callNonvirtualMethod(JNIEnv * env, jobject obj){
//    //获取一个Man对象
//    jclass cls = (*env)->GetObjectClass(env, obj);
//    jfieldID fid = (*env)->GetFieldID(env, cls, "human", "Lcom/tz/jni/Human;");
//    jobject human_obj = (*env)->GetObjectField(env, obj, fid);
//
//    //执行sayHi方法
//    jclass human_cls = (*env)->FindClass(env, "com/tz/jni/Human");//注意：传父类的类名
//    jmethodID mid = (*env)->GetMethodID(env, human_cls, "sayHi", "()Ljava/lang/String;");
//
//    //执行子类覆盖的方法
//    //jstring jstr = (*env)->CallObjectMethod(env, human_obj, mid);
//    //执行父类的方法
//    jstring jstr = (*env)->CallNonvirtualObjectMethod(env, human_obj, human_cls, mid);
//
//    //jstring->char*
//    char * str = (*env)->GetStringUTFChars(env, jstr, NULL);
//    FILE *fp = fopen("D://log.txt", "w");
//    fputs(str, fp);
//    fclose(fp);
//
//}

//中文字符串乱码
//JNIEXPORT jstring JNICALL Java_com_tz_jni_TestNative_chineseChars(JNIEnv * env, jobject obj,jstring jstr){
//    //java中传入的中文->C字符串
//    /*char * str = (*env)->GetStringUTFChars(env, jstr, NULL);
//    FILE *fp = fopen("D://log.txt", "w");
//    fputs(str, fp);
//    fclose(fp);*/
//
//    //C字符串->jstring
//    char *cstr = "我说中文";
//    //jstring j_str = (*env)->NewStringUTF(env, cstr);
//    //借用Java的转码API，返回GB2312中文编码字符串
//    //使用这个构造方法，完成转码
//    //public String(byte bytes[], String charsetName)
//    //执行这个构造方法需要三个东西
//    //1.jmethodID
//    //2.byte数组(jbyteArray)参数
//    //3.charsetName参数(jstring)
//
//    //String类的jclass
//    jclass str_cls = (*env)->FindClass(env, "java/lang/String");
//    jmethodID constructor_mid = (*env)->GetMethodID(env, str_cls, "<init>", "([BLjava/lang/String;)V");
//
//    //char * -> char[] ->jbyteArray -> jbyte *
//    jbyteArray bytes = (*env)->NewByteArray(env, strlen(cstr));
//    //bytes数组赋值
//    (*env)->SetByteArrayRegion(env, bytes, 0, strlen(cstr), cstr);
//
//    //charsetName="GB2312"
//    jstring charsetName = (*env)->NewStringUTF(env, "GB2312");
//
//    //返回GB2312中文编码jstring
//    return (*env)->NewObject(env, str_cls, constructor_mid, bytes, charsetName);
//}

