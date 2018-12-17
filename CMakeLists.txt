cmake_minimum_required(VERSION 3.2)
project(aben)

include(CMakeListsPrivate.txt)

add_custom_target(
        PLATFORMIO_BUILD ALL
        COMMAND ${PLATFORMIO_CMD} -f -c clion run
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
        PLATFORMIO_UPLOAD ALL
        COMMAND ${PLATFORMIO_CMD} -f -c clion run --target upload
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
        PLATFORMIO_CLEAN ALL
        COMMAND ${PLATFORMIO_CMD} -f -c clion run --target clean
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
        PLATFORMIO_TEST ALL
        COMMAND ${PLATFORMIO_CMD} -f -c clion test
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
        PLATFORMIO_PROGRAM ALL
        COMMAND ${PLATFORMIO_CMD} -f -c clion run --target program
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
        PLATFORMIO_UPLOADFS ALL
        COMMAND ${PLATFORMIO_CMD} -f -c clion run --target uploadfs
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
        PLATFORMIO_UPDATE_ALL ALL
        COMMAND ${PLATFORMIO_CMD} -f -c clion update
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
        PLATFORMIO_REBUILD_PROJECT_INDEX ALL
        COMMAND ${PLATFORMIO_CMD} -f -c clion init --ide clion
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(${PROJECT_NAME} ${SRC_LIST} src/controller/scene/show/animation/KeyPoint.cpp src/controller/scene/show/animation/KeyPoint.h src/controller/scene/show/animation/KeyPointType.h src/settings/model/IDataModel.cpp src/settings/model/IDataModel.h src/settings/model/DataModel.cpp src/settings/model/DataModel.h src/settings/eeprom/IEEPROMDataModel.cpp src/settings/eeprom/IEEPROMDataModel.h src/settings/osc/IOSCDataModel.cpp src/settings/osc/IOSCDataModel.h src/settings/osc/OSCDataRouter.cpp src/settings/osc/OSCDataRouter.h src/settings/eeprom/EEPROMStorage.cpp src/settings/eeprom/EEPROMStorage.h)
