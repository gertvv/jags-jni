#include <iostream>
#include <string>
#include <list>

#include <model/Model.h>
#include "Model.h"

using std::cout;
using std::cerr;
using std::endl;

Model *getModel(JNIEnv *env, jobject jobj) {
	jclass cls = env->GetObjectClass(jobj);
	jfieldID fid = env->GetFieldID(cls, "d_ptr", "J");
	return (Model *)env->GetLongField(jobj, fid);
}

/*
 * Class:     fr.iarc.jags.model.Model
 * Method:    initialize
 */
JNIEXPORT void JNICALL Java_fr_iarc_jags_model_Model_initialize
  (JNIEnv *, jobject, jboolean) {
	cout << "Model.initialize" << endl;
}

/*
 * Class:     fr.iarc.jags.model.Model
 * Method:    isInitialized
 */
JNIEXPORT jboolean JNICALL Java_fr_iarc_jags_model_Model_isInitialized
  (JNIEnv *env, jobject jobj) {
	return (jboolean) getModel(env, jobj)->isInitialized();
}

/*
 * Class:     fr.iarc.jags.model.Model
 * Method:    update
 */
JNIEXPORT void JNICALL Java_fr_iarc_jags_model_Model_update
  (JNIEnv *, jobject, jint) {
	cout << "Model.update" << endl;
}

/*
 * Class:     fr.iarc.jags.model.Model
 * Method:    getCurrentIteration
 */
JNIEXPORT jint JNICALL Java_fr_iarc_jags_model_Model_getCurrentIteration
  (JNIEnv *env, jobject jobj) {
	return (jint) getModel(env, jobj)->iteration();
}

/*
 * Class:     fr.iarc.jags.model.Model
 * Method:    addMonitor
 */
JNIEXPORT void JNICALL Java_fr_iarc_jags_model_Model_addMonitor
  (JNIEnv *, jobject, jobject) {
	cout << "Model.addMonitor" << endl;
}

/*
 * Class:     fr.iarc.jags.model.Model
 * Method:    removeMonitor
 */
JNIEXPORT void JNICALL Java_fr_iarc_jags_model_Model_removeMonitor
  (JNIEnv *, jobject, jobject) {
	cout << "Model.removeMonitor" << endl;
}

/*
 * Class:     fr.iarc.jags.model.Model
 * Method:    nChains
 */
JNIEXPORT jint JNICALL Java_fr_iarc_jags_model_Model_nChains
  (JNIEnv *env, jobject jobj) {
	return (jint) getModel(env, jobj)->nchain();
}

/*
 * Class:     fr.iarc.jags.model.Model
 * Method:    setRandomNumberGenerator
 */
JNIEXPORT jboolean JNICALL Java_fr_iarc_jags_model_Model_setRandomNumberGenerator
  (JNIEnv *, jobject, jstring, jint) {
	cout << "Model.setRandomNumberGenerator" << endl;
}

/*
 * Class:     fr.iarc.jags.model.Model
 * Method:    stopAdapting
 */
JNIEXPORT jboolean JNICALL Java_fr_iarc_jags_model_Model_stopAdapting
  (JNIEnv *, jobject) {
	cout << "Model.stopAdapting" << endl;
}

/*
 * Class:     fr.iarc.jags.model.Model
 * Method:    isAdapting
 */
JNIEXPORT jboolean JNICALL Java_fr_iarc_jags_model_Model_isAdapting
  (JNIEnv *env, jobject jobj) {
	return (jboolean) getModel(env, jobj)->isAdapting();
}

/*
 * Class:     fr.iarc.jags.model.Model
 * Method:    construct
 */
JNIEXPORT jlong JNICALL Java_fr_iarc_jags_model_Model_construct
  (JNIEnv *env, jobject obj, jint nChains) {
	Model *model = new Model((int)nChains);
	return ((jlong) model);
}

/*
 * Class:     fr.iarc.jags.model.Model
 * Method:    destruct
 */
JNIEXPORT void JNICALL Java_fr_iarc_jags_model_Model_destruct
  (JNIEnv *env, jobject jobj) {
	delete getModel(env, jobj);
}

/*
 * Class:     fr.iarc.jags.model.Model
 * Method:    addStochasticNode
 */
JNIEXPORT void JNICALL Java_fr_iarc_jags_model_Model_addStochasticNode(
		JNIEnv *env, jobject model,
		jobject node, jstring distr, jobjectArray parents,
		jobject lower, jobject upper) {
	cout << "Model.addStochasticNode" << endl;
}


/*
 * Class:     fr.iarc.jags.model.Model
 * Method:    addDeterministicNode
 */
JNIEXPORT void JNICALL Java_fr_iarc_jags_model_Model_addDeterministicNode(
		JNIEnv *env, jobject model,
		jobject node, jstring func, jobjectArray parents) {
	cout << "Model.addDeterministicNode" << endl;
}

/*
 * Class:     fr.iarc.jags.model.Model
 * Method:    addConstantNode
 */
JNIEXPORT void JNICALL Java_fr_iarc_jags_model_Model_addConstantNode(
		JNIEnv *env, jobject model,
		jobject node, jintArray dim, jdoubleArray values) {
	cout << "Model.addConstantNode" << endl;
}
