cmake_minimum_required(VERSION 2.8)

#Nom du projet

project(MoOS)

include_directories(${PROJECT_SOURCE_DIR}/lib/lo
	"${PROJECT_SOURCE_DIR}"
	"${PROJECT_SOURCE_DIR}/capture/*"
	"${PROJECT_SOURCE_DIR}/Inputs/*"
	"${PROJECT_SOURCE_DIR}/mapping/*"
	"${PROJECT_SOURCE_DIR}/outputs/*"
	"${PROJECT_SOURCE_DIR}/processings/*"
	"${PROJECT_SOURCE_DIR}/save/*"
	"${PROJECT_SOURCE_DIR}/utils/*"
	"${PROJECT_SOURCE_DIR}/view/*"

)
link_directories(
	${PROJECT_SOURCE_DIR}/lib/lo/
	${PROJECT_SOURCE_DIR}
	${PROJECT_SOURCE_DIR}/capture/*
	${PROJECT_SOURCE_DIR}/Inputs/*
	${PROJECT_SOURCE_DIR}/mapping/*
	${PROJECT_SOURCE_DIR}/outputs/*
	${PROJECT_SOURCE_DIR}/processings/*
	${PROJECT_SOURCE_DIR}/save/*
	${PROJECT_SOURCE_DIR}/utils/*
	${PROJECT_SOURCE_DIR}/view/*
)

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
	bin/MoOS 
	${source_files}	
)

target_link_libraries(
	${CMAKE_CURRENT_SOURCE_DIR}/lib/lo/liblo.dylib
)