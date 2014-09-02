cmake_minimum_required(VERSION 2.8)

#Nom du projet

project(MOOS)


SET( Boost_USE_MULTITHREAD ON )
SET( Boost_USE_STATIC_LIBS FALSE )
SET(BOOST_MIN_VERSION "1.53.0")

FIND_PACKAGE(Liblo)
IF(LIBLO_FOUND)
	message ("ok LIBLO found")
        SET(MOOS_INCLUDE_DIRS ${MOOS_INCLUDE_DIRS} "${LIBLO_INCLUDE_DIR}")
        SET(MOOS_LIBS ${MOOS_LIBS} "${LIBLO_LIBRARIES}")
ELSE()
  message (FATAL_ERROR "Could not find LIBLO libraries!")
ENDIF(LIBLO_FOUND)

FIND_PACKAGE(Gecode)
IF(GECODE_FOUND)
	message ("ok GECODE found")
        SET(MOOS_INCLUDE_DIRS ${MOOS_INCLUDE_DIRS} "${Gecode_INCLUDE_DIRS}")
        SET(MOOS_LIBS ${MOOS_LIBS} "${Gecode_LIBRARIES}")
ELSE()
  message (FATAL_ERROR "Could not find GECODE libraries!")
ENDIF(GECODE_FOUND)

FIND_PACKAGE(Pcap)
IF(PCAP_FOUND)
	message ("ok PCAP found")
        SET(MOOS_INCLUDE_DIRS ${MOOS_INCLUDE_DIRS} "${PCAP_INCLUDE_DIR}")
        SET(MOOS_LIBS ${MOOS_LIBS} "${PCAP_LIBRARY}")
ELSE()
  message (FATAL_ERROR "Could not find PCAP libraries!")
ENDIF(PCAP_FOUND)

        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fpermissive")


FIND_PACKAGE( Boost REQUIRED thread system serialization)

IF(Boost_FOUND)
	message ("ok boost found")
  SET(MOOS_INCLUDE_DIRS ${MOOS_INCLUDE_DIRS} "${Boost_INCLUDE_DIR}")
  SET(MOOS_LIBS ${MOOS_LIBS} "${Boost_LIBRARIES}")
ELSE()
  message (FATAL_ERROR "Could not find Boost libraries!")
ENDIF(Boost_FOUND)

include_directories(
        "${MOOS_INCLUDE_DIRS}"
	"${PROJECT_SOURCE_DIR}"
	"${PROJECT_SOURCE_DIR}/capture/"
	"${PROJECT_SOURCE_DIR}/Inputs/"
	"${PROJECT_SOURCE_DIR}/mapping/"
	"${PROJECT_SOURCE_DIR}/outputs/"
	"${PROJECT_SOURCE_DIR}/processings/"
	"${PROJECT_SOURCE_DIR}/save/"
	"${PROJECT_SOURCE_DIR}/utils/"
	"${PROJECT_SOURCE_DIR}/view/server/"

)
#link_directories(
#	${PROJECT_SOURCE_DIR}
#	${PROJECT_SOURCE_DIR}/capture/*
#	${PROJECT_SOURCE_DIR}/Inputs/*
#	${PROJECT_SOURCE_DIR}/mapping/*
#	${PROJECT_SOURCE_DIR}/outputs/*
#	${PROJECT_SOURCE_DIR}/processings/*
#	${PROJECT_SOURCE_DIR}/save/*
#	${PROJECT_SOURCE_DIR}/utils/*
#	${PROJECT_SOURCE_DIR}/view/server/*
#)



#TARGET_LINK_LIBRARIES(${LIBLO_LIBRARIES} ${Boost_LIBRARIES})
#Déclaration executable


file(
	GLOB_RECURSE
	source_files
	LibLoAndCap/*
	./AppIncludes.h
	./capture/*
	./Inputs/*
	./mapping/*
	./outputs/*
	./processings/*
	./save/*
	./utils/*
	./view/*
)


add_executable(
	MoOS
	${source_files}
)

target_link_libraries(MoOS ${MOOS_LIBS})
