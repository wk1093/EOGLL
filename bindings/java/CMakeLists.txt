
# Compile java bindings

# import cmake java module
include(UseJava)

set(Java_JAVAC_EXECUTABLE C:/Users/101195053/.jdks/corretto-21.0.4/bin/javac)
set(Java_JAVAH_EXECUTABLE C:/Users/101195053/.jdks/corretto-21.0.4/bin/javah)
set(Java_JAVADOC_EXECUTABLE C:/Users/101195053/.jdks/corretto-21.0.4/bin/javadoc)
set(Java_JAR_EXECUTABLE C:/Users/101195053/.jdks/corretto-21.0.4/bin/jar)

add_library(eogll_windowhints SHARED src/WindowHints.c)
target_link_libraries(eogll_windowhints eogll)
target_include_directories(eogll_windowhints PUBLIC C:/Users/101195053/.jdks/corretto-21.0.4/include C:/Users/101195053/.jdks/corretto-21.0.4/include/win32)
# change libwindowhints.dll to windowhints.dll
set(CMAKE_SHARED_LIBRARY_PREFIX "")


add_jar(
        eogll_java
        SOURCES
        src/WindowHints.java
        src/Main.java
        ENTRY_POINT
        "Main"
)
add_dependencies(eogll_java eogll_windowhints)