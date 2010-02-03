#ifndef _JAGS_JNI_UTIL_H_
#define _JAGS_JNI_UTIL_H_

#include <jni.h>

class Monitor;
class Node;
class Model;

Monitor *getMonitor(JNIEnv *env, jobject jobj);
Node *getNode(JNIEnv *env, jobject jobj);
Model *getModel(JNIEnv *env, jobject jobj);

#endif // _JAGS_JNI_UTIL_H_
