export DUYE_ROOT=/`whoami`/output/duye
export DUYE_LIB=$DUYE_ROOT/lib
export DUYE_BIN=$DUYE_ROOT/bin

echo "DUYE_ROOT=$DUYE_ROOT"
echo "DUYE_LIB=$DUYE_LIB"
echo "DUYE_BIN=$DUYE_BIN"

mkdir $DUYE_LIB -p
mkdir $DUYE_BIN -p
