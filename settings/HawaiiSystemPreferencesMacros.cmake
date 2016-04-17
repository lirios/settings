#.rst
# HawaiiSystemPreferencesMacros
# -----------------------------
#
# This module provides the ``add_hawaii_preflet`` and ``add_hawaii_preferences_shell``
# functions for adding preflets and preferences shells.
#
# ::
#
#   add_hawaii_preflet(VENDOR <vendor>
#                      NAME <name>
#                      CONTENTS_DIR <qml_contents_directory>
#                      METADATA_TEMPLATE <metadata_desktop>
#                      [SOURCES <file> [<file> [...]]]
#                      [COMPONENT <component>]
#                      [UPDATE_TRANSLATIONS]
#                      [QM_FILES_VAR <qm_files_var>]
#                      [DESKTOP_FILE_VAR <desktop_file_var>]
#
# Install the <qml_contents_directory> directory to the preflet location for
# the vendor <vendor>, ``<sharedir>/hawaii-system-preferences/modules/<vendor>/<name>``.
#
# ``add_hawaii_preflet`` creates the ``<name>_translations`` target that will
# build the .qm files for translations and the metadata.desktop with
# translated entries from the "translations" directory relative to the
# sources directory.
#
# Translations will be installed into
# ``<sharedir>/hawaii-system-preferences/translations/modules/<vendor>``.
#
# Pass UPDATE_TRANSLATIONS to update the translation template and all
# translations.
#
# Translation output .qm files are added to the <qm_files_var> target.
#
# ::
#
#   add_hawaii_preferences_shell(VENDOR <vendor>
#                                NAME <name>
#                                CONTENTS_DIR <qml_contents_directory>
#                                [UPDATE_TRANSLATIONS]
#                                [QM_FILES_VAR <qm_files_var>])
#
# Installs the <qml_contents_directory> directory to the shells location
# for the vendor <vendor>, ``<sharedir>/hawaii-system-preferences/shells/<vendor>/<name>``.
#
# ``add_hawaii_preferences_shell`` creates the ``<name>_translations``
# target that will build the .qm files for translations.
#
# Translations will be installed into
# ``<sharedir>/hawaii-system-preferences/translations/shells/<vendor>``.
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
# (To distribute this file outside of Hawaii, substitute the full
#  License text for the above reference.)

include(CMakeParseArguments)

function(add_hawaii_preflet)
    # Parse arguments
    set(options UPDATE_TRANSLATIONS)
    set(oneValueArgs VENDOR NAME METADATA_TEMPLATE CONTENTS_DIR COMPONENT QM_FILES_VAR DESKTOP_FILE_VAR)
    set(multiValueArgs SOURCES)
    cmake_parse_arguments(ARGS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if(ARGS_UNPARSED_ARGUMENTS)
        message(FATAL_ERROR "Unknown keywords given to add_hawaii_preflet(): \"${ARGS_UNPARSED_ARGUMENTS}\"")
    endif()

    if(NOT DEFINED ARGS_COMPONENT)
        set(ARGS_COMPONENT "Runtime")
    endif()

    set(install_dir "${DATA_INSTALL_DIR}/hawaii-system-preferences/modules/${ARGS_VENDOR}/${ARGS_NAME}")
    set(translations_dir "${DATA_INSTALL_DIR}/hawaii-system-preferences/translations/modules/${ARGS_VENDOR}")

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

    hawaii_translate_desktop(desktop_file
                             SOURCES ${ARGS_METADATA_TEMPLATE})
    install(FILES ${desktop_file}
            DESTINATION ${install_dir}
            RENAME metadata.desktop
            COMPONENT "${ARGS_COMPONENT}")

    if(${ARGS_UPDATE_TRANSLATIONS})
        hawaii_translate_ts(qm_files
                            SOURCES ${ARGS_CONTENTS_DIR} ${ARGS_SOURCES}
                            TEMPLATE ${ARGS_NAME}
                            INSTALL_DIR ${translations_dir}
                            UPDATE_TRANSLATIONS
                            COMPONENT "${ARGS_COMPONENT}")
    else()
        hawaii_translate_ts(qm_files
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


function(add_hawaii_preferences_shell)
    # Parse arguments
    set(options UPDATE_TRANSLATIONS)
    set(oneValueArgs VENDOR NAME CONTENTS_DIR COMPONENT)
    set(multiValueArgs SOURCES)
    cmake_parse_arguments(ARGS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if(ARGS_UNPARSED_ARGUMENTS)
        message(FATAL_ERROR "Unknown keywords given to add_hawaii_preferences_shell(): \"${ARGS_UNPARSED_ARGUMENTS}\"")
    endif()

    if(NOT DEFINED ARGS_COMPONENT)
        set(ARGS_COMPONENT "Runtime")
    endif()

    set(install_dir "${DATA_INSTALL_DIR}/hawaii-system-preferences/shells/${ARGS_VENDOR}/${ARGS_NAME}")
    set(translations_dir "${DATA_INSTALL_DIR}/hawaii-system-preferences/translations/shells/${ARGS_VENDOR}/${ARGS_NAME}")

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

    if(${ARGS_UPDATE_TRANSLATIONS})
        hawaii_translate_ts(qm_files
                            SOURCES ${ARGS_CONTENTS_DIR} ${ARGS_SOURCES}
                            TEMPLATE ${ARGS_NAME}
                            INSTALL_DIR ${translations_dir}
                            UPDATE_TRANSLATIONS
                            COMPONENT "${ARGS_COMPONENT}")
    else()
        hawaii_translate_ts(qm_files
                            SOURCES ${ARGS_CONTENTS_DIR} ${ARGS_SOURCES}
                            TEMPLATE ${ARGS_NAME}
                            INSTALL_DIR ${translations_dir}
                            COMPONENT "${ARGS_COMPONENT}")
    endif()

    add_custom_target(${ARGS_NAME}_translations ALL DEPENDS ${qm_files})

    if(DEFINED ARGS_QM_FILES_VAR)
        set(${ARGS_QM_FILES_VAR} ${qm_files} PARENT_SCOPE)
    endif()
endfunction()
