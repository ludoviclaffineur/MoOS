cmake_minimum_required(VERSION 2.8)

#Nom du projet

project(MoOS)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/lo)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/lo)

#Déclaration executable

file(
	GLOB_RECURSE
	source_files
	LibLoAndCap/*
	capture/*
	Inputs/*
	mapping/*
	outputs/*
	processings/*
	save/*
	utils/*
	view/*
)


add_executable(
	bin/MoOS ${source_file}	
)

target_link_libraries(
	${CMAKE_CURRENT_SOURCE_DIR}lib/lo
	"liblo"
)