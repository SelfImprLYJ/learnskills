package com.example.user.jnistudy;

/**
 * Created by user on 18-6-12.
 */

public class JniUtil {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    private String key = "liyongjian's key";//非静态属性

    public static int count = 10;//静态属性

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public static native String stringFromJNI();

    public static native String stringFromC();

    public static native String myJNIEnv();

    public  native String accessFiled();//c访问非静态属性

    public static native void accessStaticFiled();//c访问静态属性

    public native int accessMethod();//c访问非静态方法

    public static native void accessStaticMethod(String path);//c访问静态方法

    public static native void accessConstructor(String path);//c访问java构造方法

    public static native void giveArray(int[] intArray);

//    (II)I

    public int getSumInt(int num,int num2){
        return num + num2;
    }

    public static String getFileName(){
        return "我是文件名字";
    }
}
