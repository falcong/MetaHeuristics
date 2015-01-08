cmake_minimum_required(VERSION 2.6)
######################################################################################
### 0) Include the install configuration file where are defined the main variables
######################################################################################

INCLUDE(${CMAKE_SOURCE_DIR}/install.cmake)

######################################################################################


######################################################################################
### 1) Set your application properties
######################################################################################

# Define your project name
PROJECT(MetaH)

######################################################################################


######################################################################################
### 2) Include the sources
######################################################################################

INCLUDE_DIRECTORIES(${PARADISEO_EO_SRC_DIR}/src
                    ${PARADISEO_MO_SRC_DIR}/src )

INCLUDE_DIRECTORIES(${PARADISEO_EO_SRC_DIR}/src
                    ${PARADISEO_MO_SRC_DIR}/src
                    ${PARADISEO_MOEO_SRC_DIR}/src
                    ${PARADISEO_PEO_SRC_DIR}/src)

######################################################################################


######################################################################################
### 3) Specify where CMake can find the libraries
######################################################################################

# Link with the EO library directory, only if you need it
LINK_DIRECTORIES(${PARADISEO_EO_BIN_DIR}/lib)

# Link with the MOEO library directory, only if you need it
LINK_DIRECTORIES(${PARADISEO_MOEO_BIN_DIR}/lib)

# Link with the PEO library directory, only if you need it
LINK_DIRECTORIES(${PARADISEO_PEO_BIN_DIR}/lib)

######################################################################################



######################################################################################
### 4) Define your target: just an executable here
######################################################################################

ADD_EXECUTABLE(localizacion localizacion.cpp)
ADD_EXECUTABLE(localizacionHCFirstImpr localizacionHCFirstImpr.cpp)
ADD_EXECUTABLE(localizacionNeutralHC localizacionNeutralHC.cpp)
ADD_EXECUTABLE(localizacionSA localizacionSA.cpp)
ADD_EXECUTABLE(localizacionTS localizacionTS.cpp)
ADD_EXECUTABLE(localizacionILS localizacionILS.cpp)
ADD_EXECUTABLE(localizacionVNS localizacionVNS.cpp)
ADD_EXECUTABLE(pmediana pmediana.cpp)
ADD_EXECUTABLE(pmedianaHCFirstImpr pmedianaHCFirstImpr.cpp)
ADD_EXECUTABLE(pmedianaNeutralHC pmedianaNeutralHC.cpp)
ADD_EXECUTABLE(pmedianaSA100step pmedianaSA100step.cpp)
ADD_EXECUTABLE(pmedianaSA500step pmedianaSA500step.cpp)
ADD_EXECUTABLE(pmedianaILS pmedianaILS.cpp)
ADD_EXECUTABLE(pmedianaTS pmedianaTS.cpp)
ADD_EXECUTABLE(pmedianaVNS pmedianaVNS.cpp)
ADD_EXECUTABLE(pcentro pcentro.cpp)
ADD_EXECUTABLE(pcentroHCFirstImpr pcentroHCFirstImpr.cpp)
ADD_EXECUTABLE(pcentroNeutralHC pcentroNeutralHC.cpp)
ADD_EXECUTABLE(pcentroSA100step pcentroSA100step.cpp)
ADD_EXECUTABLE(pcentroSA500step pcentroSA500step.cpp)
ADD_EXECUTABLE(pcentroILS pcentroILS.cpp)
ADD_EXECUTABLE(pcentroTS pcentroTS.cpp)
ADD_EXECUTABLE(pcentroVNS pcentroVNS.cpp)
######################################################################################


######################################################################################
### 5) Link the libraries for your executable
######################################################################################

# Only if you need to link libraries
TARGET_LINK_LIBRARIES(localizacion ga eo eoutils)
TARGET_LINK_LIBRARIES(localizacionHCFirstImpr ga eo eoutils)
TARGET_LINK_LIBRARIES(localizacionNeutralHC ga eo eoutils)
TARGET_LINK_LIBRARIES(localizacionSA ga eo eoutils)
TARGET_LINK_LIBRARIES(localizacionTS ga eo eoutils)
TARGET_LINK_LIBRARIES(localizacionILS ga eo eoutils)
TARGET_LINK_LIBRARIES(localizacionVNS ga eo eoutils)
TARGET_LINK_LIBRARIES(pmediana ga eo eoutils)
TARGET_LINK_LIBRARIES(pmedianaHCFirstImpr ga eo eoutils)
TARGET_LINK_LIBRARIES(pmedianaNeutralHC ga eo eoutils)
TARGET_LINK_LIBRARIES(pmedianaSA100step ga eo eoutils)
TARGET_LINK_LIBRARIES(pmedianaSA500step ga eo eoutils)
TARGET_LINK_LIBRARIES(pmedianaILS ga eo eoutils)
TARGET_LINK_LIBRARIES(pmedianaTS ga eo eoutils)
TARGET_LINK_LIBRARIES(pmedianaVNS ga eo eoutils)
TARGET_LINK_LIBRARIES(pcentro ga eo eoutils)
TARGET_LINK_LIBRARIES(pcentroHCFirstImpr ga eo eoutils)
TARGET_LINK_LIBRARIES(pcentroNeutralHC ga eo eoutils)
TARGET_LINK_LIBRARIES(pcentroSA100step ga eo eoutils)
TARGET_LINK_LIBRARIES(pcentroSA500step ga eo eoutils)
TARGET_LINK_LIBRARIES(pcentroILS ga eo eoutils)
TARGET_LINK_LIBRARIES(pcentroTS ga eo eoutils)
TARGET_LINK_LIBRARIES(pcentroVNS ga eo eoutils)
######################################################################################






