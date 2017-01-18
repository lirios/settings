#.rst
# LiriSettingsMacros
# -----------------------------
#
# This module provides the ``add_liri_preflet`` and ``add_liri_preferences_shell``
# functions for adding preflets and preferences shells.
#
# ::
#
#   add_liri_preflet(NAME <name>
#                    CONTENTS_DIR <qml_contents_directory>
#                    METADATA_TEMPLATE <metadata_desktop>
#                    [SOURCES <file> [<file> [...]]]
#                    [COMPONENT <component>]
#                    [UPDATE_TRANSLATIONS]
#                    [QM_FILES_VAR <qm_files_var>]
#                    [DESKTOP_FILE_VAR <desktop_file_var>]
#
# Install the <qml_contents_directory> directory to the preflet location
# ``<sharedir>/liri/settings/modules/<name>``.
#
# ``add_liri_preflet`` creates the ``<name>_translations`` target that will
# build the .qm files for translations and the metadata.desktop with
# translated entries from the "translations" directory relative to the
# sources directory.
#
# Translations will be installed into
# ``<sharedir>/liri/settings/translations/modules``.
#
# Pass UPDATE_TRANSLATIONS to update the translation template and all
# translations.
#
# Translation output .qm files are added to the <qm_files_var> target.
#

#=============================================================================
# Copyright 2016 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
#
# Distributed under the OSI-approved BSD License (the "License");
# see accompanying file COPYING-CMAKE-SCRIPTS for details.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================
# (To distribute this file outside of Liri, substitute the full
#  License text for the above reference.)

include(CMakeParseArguments)

function(add_liri_preflet)
    # Parse arguments
    set(options UPDATE_TRANSLATIONS)
    set(oneValueArgs NAME METADATA_TEMPLATE CONTENTS_DIR COMPONENT QM_FILES_VAR DESKTOP_FILE_VAR)
    set(multiValueArgs SOURCES)
    cmake_parse_arguments(ARGS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if(ARGS_UNPARSED_ARGUMENTS)
        message(FATAL_ERROR "Unknown keywords given to add_liri_preflet(): \"${ARGS_UNPARSED_ARGUMENTS}\"")
    endif()

    if(NOT DEFINED ARGS_COMPONENT)
        set(ARGS_COMPONENT "Runtime")
    endif()

    set(install_dir "${DATA_INSTALL_DIR}/liri/settings/modules/${ARGS_NAME}")
    set(translations_dir "${DATA_INSTALL_DIR}/liri/settings/translations/modules")

    install(DIRECTORY ${ARGS_CONTENTS_DIR}/
            DESTINATION ${install_dir}
            COMPONENT "${ARGS_COMPONENT}"
            PATTERN .svn EXCLUDE
            PATTERN CMakeLists.txt EXCLUDE
            PATTERN Messages.sh EXCLUDE
            PATTERN dummydata EXCLUDE
            PATTERN *.desktop.in EXCLUDE
            PATTERN resources EXCLUDE
            PATTERN translations EXCLUDE)

    vibe_translate_desktop(desktop_file
                           SOURCES ${ARGS_METADATA_TEMPLATE})
    install(FILES ${desktop_file}
            DESTINATION ${install_dir}
            RENAME metadata.desktop
            COMPONENT "${ARGS_COMPONENT}")

    if(${ARGS_UPDATE_TRANSLATIONS})
        vibe_translate_ts(qm_files
                          SOURCES ${ARGS_CONTENTS_DIR} ${ARGS_SOURCES}
                          TEMPLATE ${ARGS_NAME}
                          INSTALL_DIR ${translations_dir}
                          UPDATE_TRANSLATIONS
                          COMPONENT "${ARGS_COMPONENT}")
    else()
        vibe_translate_ts(qm_files
                          SOURCES ${ARGS_CONTENTS_DIR} ${ARGS_SOURCES}
                          TEMPLATE ${ARGS_NAME}
                          INSTALL_DIR ${translations_dir}
                          COMPONENT "${ARGS_COMPONENT}")
    endif()

    add_custom_target(${ARGS_NAME}_translations ALL DEPENDS ${qm_files} ${desktop_file})

    if(DEFINED ARGS_QM_FILES_VAR)
        set(${ARGS_QM_FILES_VAR} ${qm_files} PARENT_SCOPE)
    endif()

    if(DEFINED ARGS_DESKTOP_FILE_VAR)
        set(${ARGS_DESKTOP_FILE_VAR} ${desktop_file} PARENT_SCOPE)
    endif()
endfunction()
