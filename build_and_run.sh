#!/bin/zsh
cmake --build ./build > /dev/null

if [ $? -eq 0 ]; then
  ./build/SimpleProject
else
  echo "Build failed."
fi
