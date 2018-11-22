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

add_executable(${PROJECT_NAME} ${SRC_LIST} src/model/light/Led.cpp src/model/light/Led.h src/model/light/RGBLed.cpp src/model/light/RGBLed.h src/model/color/RGBColor.cpp src/model/color/RGBColor.h src/model/color/HSVColor.cpp src/model/color/HSVColor.h src/model/color/ColorSpace.cpp src/model/color/ColorSpace.h src/controller/interaction/sensor/PIRMotionSensor.cpp src/controller/interaction/sensor/PIRMotionSensor.h src/controller/interaction/PIRArrayInteraction.cpp src/controller/interaction/PIRArrayInteraction.h src/controller/TimeBasedController.cpp src/controller/TimeBasedController.h)
