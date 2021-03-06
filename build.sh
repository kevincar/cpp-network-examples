#! /bin/sh

# Tutorials
cd ./tutorials

# Timer
cd ./timer

sh ./scripts/build.sh
cd ./build
./timer1 || exit 1
./timer2 || exit 1
./timer3 || exit 1
./timer4 || exit 1
./timer5 || exit 1
cd ..

cd ..	# Timer
cd ./daytimer
sh ./scripts/build.sh
cd ./build
./daytime1 localhost || exit 1
cd ..
cd ..	# Daytime

cd ..	# Tutorials

# Examples
cd ./examples

cd ./chat

sh ./scripts/build.sh
cd .. # chat

cd .. # Examples
