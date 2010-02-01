/*
 * This file is part of JAGS-JNI (JNI wrapper for the JAGS MCMC sampler).
 * JAGS-JNI is distributed from http://github.com/gertvv/jags-jni/.
 * Copyright (C) 2010  Gert van Valkenhoef.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <string>
#include <list>

#include <Module.h>
#include <ltdl.h>

#include "ModuleManager.h"

using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::list;

bool loadModule(string name) {
	lt_dlinit();
	lt_dlhandle mod = lt_dlopenext(name.c_str());
	if (mod == NULL) {
		cerr << lt_dlerror() << endl;
		return false;
	}
	// FIXME: save the handle somewhere for freeing

	Module *module = 0;
	for (list<Module*>::const_iterator p = Module::modules().begin();
			p != Module::modules().end(); ++p) {
		if ((*p)->name() == name) {
			module = *p;
			break;
		}
	}
	if (module) {
		module->load();
		return true;
	}

	cerr << "Module " << name << " failed to register" << endl;
	return false;
}

bool unloadModule(string name) {
	Module *module = 0;
	for (list<Module*>::const_iterator p = Module::modules().begin();
			p != Module::modules().end(); ++p) {
		if ((*p)->name() == name) {
			module = *p;
			break;
		}
	}
	if (module) {
		module->load();
		return true;
	}

	cerr << "Module " << name << " not registered" << endl;
	return false;
}

/*
 * Class:     fr.iarc.jags.ModuleManager
 * Method:    loadModule
 */
JNIEXPORT void JNICALL Java_fr_iarc_jags_ModuleManager_loadModule
  (JNIEnv * env, jclass jcls, jstring jName) {
	string name(env->GetStringUTFChars(jName, JNI_FALSE));
	cout << "Load Module: " << name << endl;
	cout << (loadModule(name) ? "Success" : "Failed") << endl;
}

/*
 * Class:     fr.iarc.jags.ModuleManager
 * Method:    unloadModule
 */
JNIEXPORT void JNICALL Java_fr_iarc_jags_ModuleManager_unloadModule
  (JNIEnv * env, jclass jcls, jstring jName) {
	string name(env->GetStringUTFChars(jName, JNI_FALSE));
	cout << "Unload Module: " << name << endl;
	cout << (unloadModule(name) ? "Success" : "Failed") << endl;
}
