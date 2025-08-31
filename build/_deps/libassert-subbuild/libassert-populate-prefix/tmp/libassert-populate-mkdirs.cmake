# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file LICENSE.rst or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "C:/Users/Predator/Documents/contribute/Nuvio/build/_deps/libassert-src")
  file(MAKE_DIRECTORY "C:/Users/Predator/Documents/contribute/Nuvio/build/_deps/libassert-src")
endif()
file(MAKE_DIRECTORY
  "C:/Users/Predator/Documents/contribute/Nuvio/build/_deps/libassert-build"
  "C:/Users/Predator/Documents/contribute/Nuvio/build/_deps/libassert-subbuild/libassert-populate-prefix"
  "C:/Users/Predator/Documents/contribute/Nuvio/build/_deps/libassert-subbuild/libassert-populate-prefix/tmp"
  "C:/Users/Predator/Documents/contribute/Nuvio/build/_deps/libassert-subbuild/libassert-populate-prefix/src/libassert-populate-stamp"
  "C:/Users/Predator/Documents/contribute/Nuvio/build/_deps/libassert-subbuild/libassert-populate-prefix/src"
  "C:/Users/Predator/Documents/contribute/Nuvio/build/_deps/libassert-subbuild/libassert-populate-prefix/src/libassert-populate-stamp"
)

set(configSubDirs Debug)
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/Predator/Documents/contribute/Nuvio/build/_deps/libassert-subbuild/libassert-populate-prefix/src/libassert-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/Predator/Documents/contribute/Nuvio/build/_deps/libassert-subbuild/libassert-populate-prefix/src/libassert-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
