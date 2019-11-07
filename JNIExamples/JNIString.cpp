#include <jni.h>
#include <iostream>
#include <string.h>
using namespace std;

int main(){
	
    JavaVM *jvm;       /* denotes a Java VM */
    JNIEnv *env;       /* pointer to native method interface */
    JavaVMInitArgs vm_args; /* JDK/JRE 10 VM initialization arguments */
    JavaVMOption* options = new JavaVMOption[1];
    char* s = "-Djava.class.path=.";
    options[0].optionString = s;
    vm_args.version = JNI_VERSION_10;
    vm_args.nOptions = 1;
    vm_args.options = options;
    vm_args.ignoreUnrecognized = false;
    /* load and initialize a Java VM, return a JNI interface
    * pointer in env */
    JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);
    delete options;
    /* invoke the Main.test method using the JNI */
    jclass cls = env->FindClass("Strings");
    if (cls == nullptr){
        cout << "Error: Can't find class\n";
    } else {
        jmethodID mid = env->GetStaticMethodID(cls, "printString", "()V");
        if (mid == nullptr){
            cout << "Error: Can't find method\n";
        } else {
            env->CallStaticVoidMethod(cls,mid);
        }
    }
    

    /* We are done. */
    jvm->DestroyJavaVM();







}
