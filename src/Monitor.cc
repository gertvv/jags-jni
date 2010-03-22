/*
 * This file is part of JAGS-JNI (JNI wrapper for the JAGS MCMC sampler).
 * JAGS-JNI is distributed from http://github.com/gertvv/jags-jni/.
 * Copyright (C) 2010  Gert van Valkenhoef.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, see <http://www.gnu.org/licenses/>.
 */
#include <iostream>
#include <string>
#include <vector>

#include <model/Monitor.h>

#include "Util.h"
#include "Monitor.h"

using std::vector;

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
