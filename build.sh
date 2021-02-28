#! /bin/sh

# Tutorials
pushd ./tutorials

# Timer
pushd ./timer

# Timer1
pushd ./timer1
sh ./scripts/build.sh

pushd ./build
./timer1 || exit 1
popd

popd	# Timer1

popd	# Timer

popd	# Tutorials
