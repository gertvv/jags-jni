JAVA=/usr/lib/jvm/java-1.5.0-sun

INCLUDE=-I../include -I$(JAVA)/include -I$(JAVA)/include/linux

all: libjagsjni.so Main test

.PHONY: Main

Main: java/target/classes/fr/iarc/jags/Main.class

Model.h: java/target/classes/fr/iarc/jags/model/Model.class
	javah -classpath java/target/classes -o Model.h \
		fr.iarc.jags.model.Model

ModuleManager.h: java/target/classes/fr/iarc/jags/ModuleManager.class
	javah -classpath java/target/classes -o ModuleManager.h \
		fr.iarc.jags.ModuleManager

Monitor.h:  java/target/classes/fr/iarc/jags/model/Monitor.class
	javah -classpath java/target/classes -o Monitor.h \
		fr.iarc.jags.model.Monitor

libjagsjni.so: ModuleManager.o Model.o Monitor.o
	g++ -shared -Wl -o libjagsjni.so $^ `pkg-config --libs jags` -lltdl

ModuleManager.o: ModuleManager.cc ModuleManager.h
	g++ -c $(INCLUDE) `pkg-config --cflags jags` -o ModuleManager.o ModuleManager.cc

Model.o: Model.cc Model.h
	g++ -c $(INCLUDE) `pkg-config --cflags jags` -o Model.o Model.cc

Monitor.o: Monitor.cc Monitor.h
	g++ -c $(INCLUDE) `pkg-config --cflags jags` -o Monitor.o Monitor.cc

%.class: %.java
	(cd java; mvn compile)

test: libjagsjni.so
	(cd java; LD_LIBRARY_PATH="..:/usr/local/lib/JAGS/modules-2.0.0" mvn test)
