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

# Timer5
cd ./timer5
sh ./scripts/build.sh
cd ./build
./timer5 || exit 1
cd ..
cd ..	# Timer5

cd ..	# Timer
cd ./daytimer

# Daytime 1
cd ./daytime1
sh ./scripts/build.sh
cd ./build
./daytime1 localhost || exit 1
cd ..
cd ..	# Daytime 1

# Daytime 2
cd ./daytime2
sh ./scripts/build.sh
cd ./build
cd ..
cd ..	# Daytime 2

# Daytime 3
cd ./daytime3
sh ./scripts/build.sh
cd ./build
cd ..
cd ..	# Daytime 3

cd ..	# Daytime

cd ..	# Tutorials
