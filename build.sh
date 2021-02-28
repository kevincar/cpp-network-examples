#! /bin/sh

# Tutorials
cd ./tutorials

# Timer
cd ./timer

# Timer1
cd ./timer1
sh ./scripts/build.sh

cd ./build
./timer1 || exit 1
cd ..

cd ..	# Timer1

cd ..	# Timer

cd ..	# Tutorials
