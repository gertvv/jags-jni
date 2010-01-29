#include <iostream>
#include <string>
#include <list>

#include <model/Model.h>
#include "Model.h"

using std::cout;
using std::cerr;
using std::endl;

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
  (JNIEnv *, jobject) {
	cout << "Model.isInitialized" << endl;
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
  (JNIEnv *, jobject) {
	cout << "Model.getCurrentIteration" << endl;
}

/*
 * Class:     fr_iarc_jags_model_Model
 * Method:    addMonitor
 * Signature: (Lfr/iarc/jags/model/Monitor;)V
 */
JNIEXPORT void JNICALL Java_fr_iarc_jags_model_Model_addMonitor
  (JNIEnv *, jobject, jobject) {
	cout << "Model.addMonitor" << endl;
}

/*
 * Class:     fr_iarc_jags_model_Model
 * Method:    removeMonitor
 * Signature: (Lfr/iarc/jags/model/Monitor;)V
 */
JNIEXPORT void JNICALL Java_fr_iarc_jags_model_Model_removeMonitor
  (JNIEnv *, jobject, jobject) {
	cout << "Model.removeMonitor" << endl;
}

/*
 * Class:     fr_iarc_jags_model_Model
 * Method:    nChains
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_fr_iarc_jags_model_Model_nChains
  (JNIEnv *env, jobject jobj) {
	jclass cls = env->GetObjectClass(jobj);
	jfieldID fid = env->GetFieldID(cls, "d_ptr", "J");
	Model *model = (Model *)env->GetLongField(jobj, fid);
	return (jint) model->nchain();
}

/*
 * Class:     fr_iarc_jags_model_Model
 * Method:    setRandomNumberGenerator
 * Signature: (Ljava/lang/String;I)Z
 */
JNIEXPORT jboolean JNICALL Java_fr_iarc_jags_model_Model_setRandomNumberGenerator
  (JNIEnv *, jobject, jstring, jint) {
	cout << "Model.setRandomNumberGenerator" << endl;
}

/*
 * Class:     fr_iarc_jags_model_Model
 * Method:    stopAdapting
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_fr_iarc_jags_model_Model_stopAdapting
  (JNIEnv *, jobject) {
	cout << "Model.stopAdapting" << endl;
}

/*
 * Class:     fr_iarc_jags_model_Model
 * Method:    isAdapting
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_fr_iarc_jags_model_Model_isAdapting
  (JNIEnv *, jobject) {
	cout << "Model.isAdapting" << endl;
}

/*
 * Class:     fr_iarc_jags_model_Model
 * Method:    construct
 * Signature: (I)J
 */
JNIEXPORT jlong JNICALL Java_fr_iarc_jags_model_Model_construct
  (JNIEnv *env, jobject obj, jint nChains) {
	Model *model = new Model((int)nChains);
	return ((jlong) model);
}

/*
 * Class:     fr_iarc_jags_model_Model
 * Method:    addStochasticNode
 * Signature: (Ljava/lang/String;[Lfr/iarc/jags/model/Node;Lfr/iarc/jags/model/Node;Lfr/iarc/jags/model/Node;)V
 */
JNIEXPORT void JNICALL Java_fr_iarc_jags_model_Model_addStochasticNode
  (JNIEnv *, jobject, jstring, jobjectArray, jobject, jobject) {
	cout << "Model.addStochasticNode" << endl;
}


/*
 * Class:     fr_iarc_jags_model_Model
 * Method:    addDeterministicNode
 * Signature: (Ljava/lang/String;[Lfr/iarc/jags/model/Node;)V
 */
JNIEXPORT void JNICALL Java_fr_iarc_jags_model_Model_addDeterministicNode
  (JNIEnv *, jobject, jstring, jobjectArray) {
	cout << "Model.addDeterministicNode" << endl;
}

/*
 * Class:     fr_iarc_jags_model_Model
 * Method:    addConstantNode
 * Signature: ([I[D)V
 */
JNIEXPORT void JNICALL Java_fr_iarc_jags_model_Model_addConstantNode
  (JNIEnv *, jobject, jintArray, jdoubleArray) {
	cout << "Model.addConstantNode" << endl;
}
