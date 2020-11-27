aux_source_directory(config CONFIG_SRC_LIST)
aux_source_directory(core CORE_SRC_LIST)
aux_source_directory(utils UTILS_SRC_LIST)
aux_source_directory(test TEST_SRC_LIST)

include_directories(../include)

add_executable(SEULex ${CONFIG_SRC_LIST} ${CORE_SRC_LIST} ${UTILS_SRC_LIST} ${TEST_SRC_LIST})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)