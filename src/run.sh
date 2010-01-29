#!/bin/bash

LD_LIBRARY_PATH=.:/usr/local/lib/JAGS/modules-2.0.0 java -cp java/target/classes/ fr.iarc.jags.Main $@
