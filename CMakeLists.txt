## automatically generated CMakeLists.txt file

# Declare the package
atlas_subdir( IDPhysValPlotting )

# Declare external dependencies ... default here is to include ROOT
find_package( ROOT COMPONENTS MathCore RIO Core Tree Hist )


# Declare package as a library
# Note the convention that library names get "Lib" suffix
# Any package you add to dependencies above, you should add
# to LINK_LIBRARIES line below (see the example)
#
# For packages that you only include from your source files (no headers)
# you can add them to PRIVATE_LINK_LIBRARIES instead.  Your clients will
# then not be able to see its header files.  This reduces compile time
# dependencies.  If in doubt, use LINK_LIBRARIES instead.
atlas_add_library( IDPhysValPlottingLib src/*.cxx
                   PUBLIC_HEADERS IDPhysValPlotting
                   INCLUDE_DIRS ${ROOT_INCLUDE_DIRS}
                   LINK_LIBRARIES ${ROOT_LIBRARIES} NtupleAnalysisUtils
                   PRIVATE_LINK_LIBRARIES
)

# build exes 
file(GLOB_RECURSE files "util/*.cxx")
foreach(_exeFile ${files})
    get_filename_component(_theExec ${_exeFile} NAME_WE)
    get_filename_component(_theLoc ${_exeFile} DIRECTORY)
    # we specify a folder for programs we do not want to compile. Useful during r21 transition...
    if(${_theLoc} MATCHES "DoNotBuild")
    else()
    atlas_add_executable( ${_theExec}
    ${_exeFile}
    INCLUDE_DIRS ${ROOT_INCLUDE_DIRS}
    LINK_LIBRARIES ${ROOT_LIBRARIES} IDPhysValPlottingLib )
    endif()
endforeach()
