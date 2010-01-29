JAVA=/usr/lib/jvm/java-1.5.0-sun

INCLUDE=-I../include -I$(JAVA)/include -I$(JAVA)/include/linux

all: libjagsjni.so

Model.h: java/target/classes/fr/iarc/jags/model/Model.class
	javah -classpath java/target/classes -o Model.h \
		fr.iarc.jags.model.Model

ModuleManager.h: java/target/classes/fr/iarc/jags/ModuleManager.class
	javah -classpath java/target/classes -o ModuleManager.h \
		fr.iarc.jags.ModuleManager

libjagsjni.so: ModuleManager.o Model.o
	g++ -shared -Wl -o libjagsjni.so $< `pkg-config --libs jags`

ModuleManager.o: ModuleManager.cc ModuleManager.h
	g++ -c $(INCLUDE) `pkg-config --cflags jags` -o ModuleManager.o ModuleManager.cc

Model.o: Model.cc Model.h
	g++ -c $(INCLUDE) `pkg-config --cflags jags` -o Model.o Model.cc

java/target/classes/fr/iarc/jags/ModuleManager.class: java/src/fr/iarc/jags/ModuleManager.java
	javac -sourcepath java/src/ -d java/target/classes/ java/src/fr/iarc/jags/*.java

java/target/classes/fr/iarc/jags/model/Model.class: java/src/fr/iarc/jags/model/Model.java
	javac -sourcepath java/src/ -d java/target/classes/ java/src/fr/iarc/jags/model/*.java
