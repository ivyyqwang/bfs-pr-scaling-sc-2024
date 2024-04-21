PROJ=$(cd "$(dirname "${BASH_SOURCE:-$0}")"; pwd);
echo "Setting Proj Root Path:" $PROJ
export UPTEST=$PROJ/tests/test-progs/upstream-snap/src
echo "Setting Old UpDown tests path:" $UPTEST
export SIMPATH=$PROJ/simout
echo "Setting Old UpDown Simout path:" $SIMPATH
export PATH=$PATH:$PROJ/scripts
echo "Adding ./scripts to PATH" $PATH
export UDRUNTIME=$PROJ/ext/updown
echo "Setting UD Runtime path:" $UDRUNTIME
export UPDOWN_INSTALL_DIR=$PROJ/ext/updown/install
echo "Setting UPDOWN_INSTALL_DIR:" $UPDOWN_INSTALL_DIR
export UPDOWN_SOURCE_CODE=$PROJ/ext/updown
echo "Setting UPDOWN_SOURCE_CODE:" $UPDOWN_SOURCE_CODE
export LD_LIBRARY_PATH=$UPDOWN_INSTALL_DIR/updown/lib
echo "LD_LIBRARY_PATH:" $LD_LIBRARY_PATH
export PYTHONPATH=$UPDOWN_SOURCE_CODE/udbasim/assembler:$UPDOWN_SOURCE_CODE/simruntime/src/emulator
echo "PYTHONPATH:" $PYTHONPATH

pushd $PROJ/ext/updown
source setup_env.sh