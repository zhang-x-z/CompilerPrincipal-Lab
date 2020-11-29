aux_source_directory(. TEST_DIR)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/config CONFIG_SRC_DIR)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/core CORE_SRC_DIR)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/utils UTILS_SRC_DIR)
# use tinyxml2
set(TINYXML_SRC ${PROJECT_SOURCE_DIR}/tinyxml2/tinyxml2.cpp)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(Test ${TINYXML_SRC} ${TEST_DIR} ${CONFIG_SRC_DIR} ${CORE_SRC_DIR} ${UTILS_SRC_DIR})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/test)