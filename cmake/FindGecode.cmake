# FindGecode
# ----------
# Fournit les cibles importées Gecode::gecode<composant> utilisées par MoOS.
#
# Homebrew installe une config CMake officielle (GecodeConfig.cmake) : on l'utilise
# si elle existe. Les paquets Debian/Ubuntu (libgecode-dev) n'en fournissent pas :
# on cherche alors en-têtes et bibliothèques à la main.

find_package(Gecode CONFIG QUIET)
if(Gecode_FOUND)
    return()
endif()

set(_gecode_components support kernel search int set float minimodel driver)

find_path(Gecode_INCLUDE_DIR gecode/kernel.hh)
set(_gecode_required_vars Gecode_INCLUDE_DIR)
foreach(_comp IN LISTS _gecode_components)
    find_library(Gecode_${_comp}_LIBRARY NAMES gecode${_comp})
    list(APPEND _gecode_required_vars Gecode_${_comp}_LIBRARY)
endforeach()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Gecode REQUIRED_VARS ${_gecode_required_vars})

if(Gecode_FOUND)
    foreach(_comp IN LISTS _gecode_components)
        if(NOT TARGET Gecode::gecode${_comp})
            add_library(Gecode::gecode${_comp} UNKNOWN IMPORTED)
            set_target_properties(Gecode::gecode${_comp} PROPERTIES
                IMPORTED_LOCATION "${Gecode_${_comp}_LIBRARY}"
                INTERFACE_INCLUDE_DIRECTORIES "${Gecode_INCLUDE_DIR}")
        endif()
    endforeach()
endif()

mark_as_advanced(Gecode_INCLUDE_DIR)
