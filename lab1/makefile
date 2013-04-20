PATH:=${JAVA_HOME}/bin:${PATH}
HADOOP_PATH=${hh}
NEW_CLASSPATH=${HADOOP_PATH}/hadoop-core-1.0.4.jar:${HADOOP_PATH}/lib/*:${HADOOP_PATH}/lib/jetty-ext/*:${CLASSPATH}

SRC = $(wildcard *.java)

all: build

build: ${SRC}
	${JAVA_HOME}/bin/javac -Xlint:deprecation -classpath ${NEW_CLASSPATH} ${SRC}
	${JAVA_HOME}/bin/jar cvf InvertedIndexer.jar *.class
clean:
	rm -f *.class *.jar
