#include <iostream>
#include <string>
#include <vector>
#include <list>

#include <model/Model.h>
#include <model/Monitor.h>
#include <graph/ConstantNode.h>
#include <compiler/Compiler.h>
#include <compiler/LogicalFactory.h>
#include <model/MonitorFactory.h>
#include "Model.h"

using std::cout;
using std::cerr;
using std::endl;
using std::vector;
using std::string;
using std::list;

Model *getModel(JNIEnv *env, jobject jobj) {
	jclass cls = env->GetObjectClass(jobj);
	jfieldID fid = env->GetFieldID(cls, "d_ptr", "J");
	return (Model *)env->GetLongField(jobj, fid);
}

Node *getNode(JNIEnv *env, jobject jobj) {
	jclass cls = env->GetObjectClass(jobj);
	jfieldID fid = env->GetFieldID(cls, "d_ptr", "J");
	return (Node *)env->GetLongField(jobj, fid);
}


/*
 * Class:     fr.iarc.jags.model.Model
 * Method:    initialize
 */
JNIEXPORT void JNICALL Java_fr_iarc_jags_model_Model_initialize(
		JNIEnv *env, jobject jModel, jboolean datagen) {
	cout << "Model.initialize" << endl;
	getModel(env, jModel)->initialize(datagen);
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
JNIEXPORT void JNICALL Java_fr_iarc_jags_model_Model_update(
		JNIEnv *env, jobject jModel, jint n) {
	cout << "Model.update" << endl;
	getModel(env, jModel)->update((unsigned int)n);
}

/*
 * Class:     fr.iarc.jags.model.Model
 * Method:    getCurrentIteration
 */
JNIEXPORT jint JNICALL Java_fr_iarc_jags_model_Model_getCurrentIteration
  (JNIEnv *env, jobject jobj) {
	return (jint) getModel(env, jobj)->iteration();
}

jobject createJavaMonitor(JNIEnv *env, Monitor *ptr) {
	jclass cls = env->FindClass("fr/iarc/jags/model/Monitor");
	jmethodID mid = env->GetMethodID(cls, "<init>", "(J)V");
	return env->NewObject(cls, mid, (jlong)ptr);
}

Monitor *createMonitor(Model *model, Node *node, string const &type, int thin) {
	list<MonitorFactory*> const &faclist = Model::monitorFactories();

	cerr << "Monitor for " << node << endl;

	Monitor *monitor = 0;
	for(list<MonitorFactory*>::const_iterator j = faclist.begin();
			j != faclist.end(); ++j) {
		monitor = (*j)->getMonitor(node, model, model->iteration() + 1,
			thin, type);
		if (monitor) {
			model->addMonitor(monitor);
			break;
		}
	}

	cerr << "Monitor: " << monitor << endl;
	for (list<Monitor*>::const_iterator m = model->monitors().begin();
			m != model->monitors().end(); ++m) {
		cerr << "In model: " << *m << " " << (*m)->type();
	}
	return monitor;
}

/*
 * Class:     fr.iarc.jags.model.Model
 * Method:    addTraceMonitor
 */
JNIEXPORT jobject JNICALL Java_fr_iarc_jags_model_Model_addTraceMonitor(
		JNIEnv *env, jobject jModel, jobject jNode) {
	cout << "Model.addTraceMonitor" << endl;
	Node *node = getNode(env, jNode);
	Model *model = getModel(env, jModel);
	return createJavaMonitor(env,
		createMonitor(model, node, string("trace"), 1));
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

jobject createJavaNode(JNIEnv *env, Node *ptr) {
	jclass cls = env->FindClass("fr/iarc/jags/model/Node");
	jmethodID mid = env->GetMethodID(cls, "<init>", "(J)V");
	return env->NewObject(cls, mid, (jlong)ptr);
}

/*
 * Class:     fr.iarc.jags.model.Model
 * Method:    addStochasticNode
 */
JNIEXPORT jobject JNICALL Java_fr_iarc_jags_model_Model_addStochasticNode(
		JNIEnv *env, jobject model,
		jstring distr, jobjectArray parents,
		jobject lower, jobject upper) {
	cout << "Model.addStochasticNode" << endl;
	return createJavaNode(env, 0);
}

vector<const Node *> jArrayToNodeVector(JNIEnv *env, jobjectArray jarr) {
	vector<const Node *> arr(env->GetArrayLength(jarr));
	for (int i = 0; i < arr.size(); ++i) {
		arr[i] = getNode(env, env->GetObjectArrayElement(jarr, i));
	}
	return arr;
}

/*
 * Class:     fr.iarc.jags.model.Model
 * Method:    addDeterministicNode
 */
JNIEXPORT jobject JNICALL Java_fr_iarc_jags_model_Model_addDeterministicNode(
		JNIEnv *env, jobject model,
		jstring funcName, jobjectArray jParents) {
	static LogicalFactory factory;
	vector<const Node*> parents = jArrayToNodeVector(env, jParents);
	FunctionPtr func = Compiler::funcTab().find(
		env->GetStringUTFChars(funcName, JNI_FALSE));
	Node *node = factory.getNode(func, parents, *getModel(env, model));
	cout << "Model.addDeterministicNode " << node << endl;
	return createJavaNode(env, node);
}

vector<unsigned int> jArrayToUnsignedVector(JNIEnv *env, jintArray jarr) {
	vector<unsigned int> arr(env->GetArrayLength(jarr));
	jint *earr = env->GetIntArrayElements(jarr, JNI_FALSE);
	for (int i = 0; i < arr.size(); ++i) {
		arr[i] = (unsigned int)earr[i];
	}
	return arr;
}

vector<double> jArrayToDoubleVector(JNIEnv *env, jdoubleArray jarr) {
	vector<double> arr(env->GetArrayLength(jarr));
	jdouble *earr = env->GetDoubleArrayElements(jarr, JNI_FALSE);
	for (int i = 0; i < arr.size(); ++i) {
		arr[i] = (double)earr[i];
	}
	return arr;
}

/*
 * Class:     fr.iarc.jags.model.Model
 * Method:    addConstantNode
 */
JNIEXPORT jobject JNICALL Java_fr_iarc_jags_model_Model_addConstantNode(
		JNIEnv *env, jobject model,
		jintArray jDim, jdoubleArray jValue) {
	vector<unsigned int> dim = jArrayToUnsignedVector(env, jDim);
	vector<double> value = jArrayToDoubleVector(env, jValue);
	ConstantNode *node =
		new ConstantNode(dim, value, getModel(env, model)->nchain());
	cout << "Model.addConstantNode " << node << endl;
	getModel(env, model)->addNode(node);
	return createJavaNode(env, node);
}
