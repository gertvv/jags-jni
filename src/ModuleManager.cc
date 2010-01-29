#include <iostream>
#include "ModuleManager.h"

using std::cout;
using std::endl;

/*
 * Class:     fr.iarc.jags.ModuleManager
 * Method:    loadModule
 */
JNIEXPORT void JNICALL Java_fr_iarc_jags_ModuleManager_loadModule
  (JNIEnv * env, jclass jcls, jstring name) {
	cout << "Load Module: " << env->GetStringUTFChars(name, JNI_FALSE) << endl;
}

/*
 * Class:     fr.iarc.jags.ModuleManager
 * Method:    unloadModule
 */
JNIEXPORT void JNICALL Java_fr_iarc_jags_ModuleManager_unloadModule
  (JNIEnv * env, jclass jcls, jstring name) {

}
