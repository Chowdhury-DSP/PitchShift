#!/bin/bash

if [ -z "$1" ]; then
    echo "No plugin name provided!"
    exit 1
fi

if [ -z "$2" ]; then
    echo "No plugin ID provided!"
    exit 1
fi

plugin_name=$1
plugin_id=$2
echo "Creating plugin ${plugin_name}, with ID ${plugin_id} ..."

echo "Copying source files..."
mv src/TempPlugin.h src/${plugin_name}.h
mv src/TempPlugin.cpp src/${plugin_name}.cpp

echo "Copying installer files..."
mv installers/mac/TempPlugin.pkgproj installers/mac/${plugin_name}.pkgproj
mv installers/windows/TempPlugin_Install_Script.iss installers/windows/${plugin_name}_Install_Script.iss

echo "Setting plugin ID..."
sed -i.bak -e "s/XXXX/${plugin_id}/g" CMakeLists.txt

echo "Setting up source files..."
declare -a source_files=("scripts/validate.sh" 
    "scripts/win_builds.sh"
    "scripts/mac_builds.sh"
    "CMakeLists.txt"
    "src/CMakeLists.txt"
    "src/${plugin_name}.h"
    "src/${plugin_name}.cpp"
    ".github/FUNDING.yml"
    "installers/mac/build_mac_installer.sh"
    "installers/mac/Intro.txt"
    "installers/mac/${plugin_name}.pkgproj"
    "installers/windows/build_win_installer.sh"
    "installers/windows/${plugin_name}_Install_Script.iss"
)
for file in "${source_files[@]}"; do
    sed -i.bak -e "s/TempPlugin/${plugin_name}/g" $file
done

sed -i.bak -e "s/JUCEPluginTemplate/${plugin_name}/g" README.md
sed -i.bak -e "s/JUCE Plugin Template/${plugin_name}/g" README.md

# Remove `run setup.sh` lines from Travis and README
sed -i.bak -e '42,48d' .github/workflows/cmake.yml
sed -i.bak -e '/setup.sh/{N;d;}' README.md
sed -i.bak -e '/set up plugin/d' README.md

# Clean up files we no longer need
rm *.bak
rm */*.bak
rm .github/*.bak
rm .github/*/*.bak
rm installers/*/*.bak
rm setup.sh

echo "Fetching submodules..."
git submodule update --init --recursive

# update chowdsp_utils
(
    echo "Updating submodule: chowdsp_utils..."
    cd modules/chowdsp_utils
    git fetch origin
    git checkout master
    git pull
    git log -n 1
)

# Stop tracking from template repo
git remote remove origin

# Remove old git commit history
clean_git_history(){
    git add .
    git commit -m "Set up ${plugin_name}"
    git checkout --orphan new-branch
    git add -A
    git commit -m "Initial commit"
    git branch -D main
    git branch -m main   
}

clean_git_history > /dev/null
