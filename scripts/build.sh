#!/bin/bash

## Environment ##
REPO_ROOT=`git rev-parse --show-toplevel`
REPO_NAME=`basename $REPO_ROOT`

# exit if any command fails
set -e

################################################################################
# Help                                                                         #
################################################################################
Help()
{
   echo "Script for building leetcode solutions."
   echo
   echo "Syntax: ./build.sh [-v|-h]"
   echo "Options:"
   echo "-v|--verbose Enables verbose output."
   echo "-h|--help	Prints this usage."
   echo
}


################################################################################
################################################################################
# Main program                                                                 #
################################################################################
################################################################################

## Parse command line arguments ##
POSITIONAL=()
while [[ $# -gt 0 ]]; do
   key="$1"

   case $key in
      -v|--verbose)
         set -x
         VERBOSE=1
         shift
         ;;
      -h|--help)
         Help
         shift
         exit
         ;;
      *)    # unknown option
         shift
         ;;
   esac
done

## build the docker image we are using for compiling the app ##
docker build -t $USER/build-$REPO_NAME $REPO_ROOT

## start build container from build image ##
BUILD_CONTAINER_ID=$(docker run -d -t $USER/build-$REPO_NAME)

## create a directory in the container for sources ##
docker exec -it -w /tmp $BUILD_CONTAINER_ID bash -c "mkdir $REPO_NAME"

## copy sources to build container ##
docker cp $REPO_ROOT/apps $BUILD_CONTAINER_ID:/tmp/$REPO_NAME/
docker cp $REPO_ROOT/CMakeLists.txt $BUILD_CONTAINER_ID:/tmp/$REPO_NAME/
docker cp $REPO_ROOT/CMakePresets.json $BUILD_CONTAINER_ID:/tmp/$REPO_NAME/

## list of build variants ##
declare -a targets=(
   "Debug"
   "Release"
)

## unset -e to allow us to loop through all of the builds ##
unset e

for target in "${targets[@]}"; do
   ## Create build directories ##
   docker exec -it -w /tmp/$REPO_NAME $BUILD_CONTAINER_ID mkdir -p build/$target

   ## Configure and generate build environment with CMake ##
   docker exec -it -w /tmp/$REPO_NAME $BUILD_CONTAINER_ID cmake --preset=$target -S . -B build/$target

   ## build ##
   docker exec -it -w /tmp/$REPO_NAME $BUILD_CONTAINER_ID cmake --build build/$target -- VERBOSE=$VERBOSE

   ## copy build artifacts back to local machine ##
   docker cp $BUILD_CONTAINER_ID:/tmp/$REPO_NAME/build $REPO_ROOT/
done

## turn set -e back on for cleanup ##
set -e

# stop the build container
docker stop $BUILD_CONTAINER_ID

# remove the container
docker rm $BUILD_CONTAINER_ID

# remove the image
docker rmi $USER/build-$REPO_NAME
