#!/bin/bash

plugin_name=$1
echo "Creating plugin ${plugin_name}..."

echo "Copying source files..."
mv src/TempPlugin.h src/${plugin_name}.h
mv src/TempPlugin.cpp src/${plugin_name}.cpp

echo "Setting up source files..."
declare -a source_files=("validate.sh" "win_builds.sh" "CMakeLists.txt" "src/CMakeLists.txt" "src/${plugin_name}.h" "src/${plugin_name}.cpp")
for file in "${source_files[@]}"; do
    sed -i.bak -e "s/TempPlugin/${plugin_name}/g" $file
done

# Clean up files we no longer need
rm *.bak
rm */*.bak
rm setup.sh

# Remove `run setup.sh` lines from Travis and README
sed -i -e '/setup.sh/d' .travis.yml
sed -i -e '/setup.sh/{N;d}' README.md
sed -i -e '/set up plugin/d' README.md

# Stop tracking from template repo
git remote remove origin

# Remove old git commit history
clean_git_history(){
    git add .
    git commit -m "Set up ${plugin_name}"
    git checkout --orphan new-branch
    git add -A
    git commit -m "Initial commit"
    git branch -D master
    git branch -m main   
}

clean_git_history > /dev/null
