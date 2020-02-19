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
                   LINK_LIBRARIES ${ROOT_LIBRARIES}
		                  #AthAnalysisBaseCompsLib
                   PRIVATE_LINK_LIBRARIES
		                  #Add private dependencies here
)

# if you add components (tools, algorithms) to this package
# uncomment the next lines
#atlas_add_component( IDPhysValPlotting src/components/*.cxx
#                     LINK_LIBRARIES IDPhysValPlottingLib 
#)
      
# if you add an application (exe) to this package
# declare it like this
#atlas_add_executable( MyApp src/myApp.cxx
#                      LINK_LIBRARIES IDPhysValPlottingLib
#)

# Install python modules, joboptions, and share content
atlas_install_python_modules( python/*.py )
atlas_install_joboptions( share/*.py )
atlas_install_data( data/* )
# You can access your data from code using path resolver, e.g.
# PathResolverFindCalibFile("IDPhysValPlotting/file.txt")

