JAVA=/usr/lib/jvm/java-1.5.0-sun

INCLUDE=-I../include -I$(JAVA)/include -I$(JAVA)/include/linux

all: libjagsjni.so test

maven-install: test
	(cd java; LD_LIBRARY_PATH="..:/usr/local/lib/JAGS/modules-2.0.0" mvn install)

.PHONY: test maven-install all

Model.h: java/target/classes/net/sourceforge/jags/model/Model.class
	javah -classpath java/target/classes -o Model.h \
		net.sourceforge.jags.model.Model

ModuleManager.h: java/target/classes/net/sourceforge/jags/ModuleManager.class
	javah -classpath java/target/classes -o ModuleManager.h \
		net.sourceforge.jags.ModuleManager

Monitor.h:  java/target/classes/net/sourceforge/jags/model/Monitor.class
	javah -classpath java/target/classes -o Monitor.h \
		net.sourceforge.jags.model.Monitor

libjagsjni.so: ModuleManager.o Model.o Monitor.o
	g++ -shared -Wl -o libjagsjni.so $^ `pkg-config --libs jags` -lltdl

ModuleManager.o: ModuleManager.cc ModuleManager.h Util.h
	g++ -c $(INCLUDE) `pkg-config --cflags jags` -o ModuleManager.o ModuleManager.cc

Model.o: Model.cc Model.h Util.h
	g++ -c $(INCLUDE) `pkg-config --cflags jags` -o Model.o Model.cc

Monitor.o: Monitor.cc Monitor.h Util.h
	g++ -c $(INCLUDE) `pkg-config --cflags jags` -o Monitor.o Monitor.cc

%.class: %.java
	(cd java; mvn compile)

test: libjagsjni.so
	(cd java; LD_LIBRARY_PATH="..:/usr/local/lib/JAGS/modules-2.0.0" mvn test)
