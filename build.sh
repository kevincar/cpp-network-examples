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

# Timer2
cd ./timer2
sh ./scripts/build.sh
cd ./build
./timer2 || exit 1
cd ..
cd ..	# Timer2

# Timer3
cd ./timer3
sh ./scripts/build.sh
cd ./build
./timer3 || exit 1
cd ..
cd ..	# Timer3

# Timer4
cd ./timer4
sh ./scripts/build.sh
cd ./build
./timer4 || exit 1
cd ..
cd ..	# Timer4

cd ..	# Timer

cd ..	# Tutorials
