# Tests unitaires : Boost.Test en variante header-only (aucune lib supplémentaire)
set(MOOS_UNIT_TESTS grid constrain wav http)

foreach(name ${MOOS_UNIT_TESTS})
    add_executable(test_${name} unit/test_${name}.cpp)
    target_include_directories(test_${name} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/unit)
    target_link_libraries(test_${name} PRIVATE moos_core)
    add_test(NAME unit.${name} COMMAND test_${name} --log_level=test_suite)
    set_tests_properties(unit.${name} PROPERTIES LABELS unit TIMEOUT 120)
endforeach()

# Batterie d'intégration : lance le vrai binaire et le pilote en HTTP / WebSocket / OSC
find_program(NODE_EXECUTABLE node)
if(NODE_EXECUTABLE)
    add_test(NAME integration
             COMMAND ${NODE_EXECUTABLE} --test --test-concurrency=1
                     ${CMAKE_CURRENT_SOURCE_DIR}/integration/moos.test.mjs)
    set_tests_properties(integration PROPERTIES
        LABELS integration
        TIMEOUT 180
        ENVIRONMENT "MOOS_BIN=$<TARGET_FILE:MoOS>"
        RESOURCE_LOCK osc_port_20000)
else()
    message(STATUS "node introuvable : batterie d'integration desactivee")
endif()
