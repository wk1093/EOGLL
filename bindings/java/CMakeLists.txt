
# Compile java bindings

# import cmake java module
include(UseJava)

set(Java_JAVAC_EXECUTABLE C:/Users/101195053/.jdks/corretto-21.0.4/bin/javac)
set(Java_JAVAH_EXECUTABLE C:/Users/101195053/.jdks/corretto-21.0.4/bin/javah)
set(Java_JAVADOC_EXECUTABLE C:/Users/101195053/.jdks/corretto-21.0.4/bin/javadoc)
set(Java_JAR_EXECUTABLE C:/Users/101195053/.jdks/corretto-21.0.4/bin/jar)
set(JNI_INCLUIDE_DIRS C:/Users/101195053/.jdks/corretto-21.0.4/include C:/Users/101195053/.jdks/corretto-21.0.4/include/win32)

add_library(eogll_windowhints SHARED src/WindowHints.c)
target_link_libraries(eogll_windowhints eogll)
target_include_directories(eogll_windowhints PUBLIC ${JNI_INCLUIDE_DIRS})
set(CMAKE_SHARED_LIBRARY_PREFIX "")

add_library(eogll_window SHARED src/Window.c)
target_link_libraries(eogll_window eogll)
target_include_directories(eogll_window PUBLIC ${JNI_INCLUIDE_DIRS})
set(CMAKE_SHARED_LIBRARY_PREFIX "")

add_library(eogll_main SHARED src/EogllMain.c)
target_link_libraries(eogll_main eogll)
target_include_directories(eogll_main PUBLIC ${JNI_INCLUIDE_DIRS})
set(CMAKE_SHARED_LIBRARY_PREFIX "")



add_jar(
        eogll_java
        SOURCES
        src/WindowHints.java
        src/Window.java
        src/Eogll.java
        src/Main.java
        ENTRY_POINT
        "Main"
)
add_dependencies(eogll_java eogll_windowhints)
add_dependencies(eogll_java eogll_window)
add_dependencies(eogll_java eogll_main)