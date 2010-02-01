#include <iostream>
#include <string>
#include <vector>

#include <model/Monitor.h>

#include "Monitor.h"

using std::cout;
using std::cerr;
using std::endl;
using std::vector;

Monitor *getMonitor(JNIEnv *env, jobject jobj) {
	jclass cls = env->GetObjectClass(jobj);
	jfieldID fid = env->GetFieldID(cls, "d_ptr", "J");
	return (Monitor *)env->GetLongField(jobj, fid);
}

/*
 * Class:     fr_iarc_jags_model_Monitor
 * Method:    getFirstIteration
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_fr_iarc_jags_model_Monitor_getFirstIteration(
		JNIEnv *env, jobject jMonitor) {
	return (jint) getMonitor(env, jMonitor)->start();
}

/*
 * Class:     fr_iarc_jags_model_Monitor
 * Method:    getLastIteration
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_fr_iarc_jags_model_Monitor_getLastIteration(
		JNIEnv *env, jobject jMonitor) {
	return (jint) getMonitor(env, jMonitor)->end();
}

/*
 * Class:     fr_iarc_jags_model_Monitor
 * Method:    getThinningInterval
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_fr_iarc_jags_model_Monitor_getThinningInterval(
		JNIEnv *env, jobject jMonitor) {
	return (jint) getMonitor(env, jMonitor)->thin();
}

/*
 * Class:     fr_iarc_jags_model_Monitor
 * Method:    getIterationCount
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_fr_iarc_jags_model_Monitor_getIterationCount(
		JNIEnv *env, jobject jMonitor) {
	return (jint) getMonitor(env, jMonitor)->niter();
}

/*
 * Class:     fr_iarc_jags_model_Monitor
 * Method:    getType
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_fr_iarc_jags_model_Monitor_getType(
		JNIEnv *env, jobject jMonitor) {
	return env->NewStringUTF(getMonitor(env, jMonitor)->type().c_str());
}

/*
 * Class:     fr_iarc_jags_model_Monitor
 * Method:    nChains
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_fr_iarc_jags_model_Monitor_nChains(
		JNIEnv *env, jobject jMonitor) {
	return (jint) getMonitor(env, jMonitor)->nchain();
}

jintArray vectorToJIntArray(
		JNIEnv *env, vector<unsigned int> const &v) {
	jintArray arr = env->NewIntArray(v.size());
	env->SetIntArrayRegion(arr, 0, v.size(), (jint*)&v[0]);
	return arr;
}

jdoubleArray vectorToJDoubleArray(
		JNIEnv *env, vector<double> const &v) {
	jdoubleArray arr = env->NewDoubleArray(v.size());
	env->SetDoubleArrayRegion(arr, 0, v.size(), (jdouble*)&v[0]);
	return arr;
}

/*
 * Class:     fr_iarc_jags_model_Monitor
 * Method:    dim
 * Signature: ()[I
 */
JNIEXPORT jintArray JNICALL Java_fr_iarc_jags_model_Monitor_dim(
		JNIEnv *env, jobject jMonitor) {
	return vectorToJIntArray(env, getMonitor(env, jMonitor)->dim());
}

/*
 * Class:     fr_iarc_jags_model_Monitor
 * Method:    value
 * Signature: (I)[D
 */
JNIEXPORT jdoubleArray JNICALL Java_fr_iarc_jags_model_Monitor_value(
		JNIEnv *env, jobject jMonitor, jint chain) {
	return vectorToJDoubleArray(env, getMonitor(env, jMonitor)->value(chain));
}
